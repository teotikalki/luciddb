/*
// Licensed to DynamoBI Corporation (DynamoBI) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  DynamoBI licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
*/

#ifndef Fennel_PagingTestBase_Included
#define Fennel_PagingTestBase_Included

#include "fennel/test/CacheTestBase.h"
#include "fennel/test/ThreadedTestBase.h"
#include "fennel/synch/SXMutex.h"

#include <vector>

FENNEL_BEGIN_NAMESPACE

class CachePage;

/**
 * PagingTestBase is a common base for multi-threaded tests which exercise
 * cache paging.
 */
class FENNEL_TEST_EXPORT PagingTestBase
    : virtual public CacheTestBase,
        virtual public ThreadedTestBase
{
protected:
    /**
     * Portion of each page that should be scribbled on.
     */
    uint cbPageUsable;

    /**
     * Number of random access operations to run per pass.
     */
    uint nRandomOps;

    /**
     * Checkpoint interval during multi-threaded test.
     */
    uint nSecondsBetweenCheckpoints;

    /**
     * Protects output stream.
     */
    StrictMutex logMutex;

    /**
     * SXMutex used to synchronize checkpoints with write actions.
     */
    SXMutex checkpointMutex;

    /**
     * Flag indicating that the cache should be dynamically resized
     * during the multi-threaded portion of the test.
     */
    bool bTestResize;

    uint generateRandomNumber(uint iMax);

public:
    /**
     * The various operations that can be run in the multi-threaded test.
     */
    enum OpType {
        OP_READ_SEQ,
        OP_WRITE_SEQ,
        OP_READ_RAND,
        OP_WRITE_RAND,
        OP_READ_NOWAIT,
        OP_WRITE_NOWAIT,
        OP_WRITE_SKIP,
        OP_SCRATCH,
        OP_PREFETCH,
        OP_PREFETCH_BATCH,
        OP_ALLOCATE,
        OP_DEALLOCATE,
        OP_CHECKPOINT,
        OP_RESIZE_CACHE,
        OP_MAX
    };

    explicit PagingTestBase();

    virtual ~PagingTestBase();

    /**
     * Scribbles on the contents of a page.  The data written is derived from
     * the parameter x.
     */
    virtual void fillPage(CachePage &page,uint x);

    /**
     * Verifies that the page contents are correct (based on the parameter x).
     */
    virtual void verifyPage(CachePage &page,uint x);

    virtual CachePage *lockPage(OpType opType,uint iPage) = 0;
    virtual void unlockPage(CachePage &page,LockMode lockMode) = 0;
    virtual void prefetchPage(uint iPage) = 0;
    virtual void prefetchBatch(uint iPage, uint nPagesPerBatch) = 0;

    /**
     * Carries out one operation on a page.  This involves locking the page,
     * calling verifyPage or fillPage, and then unlocking the page.
     *
     * @param opType operation which  will be attempted
     *
     * @param iPage block number of page
     *
     * @param bNice true if page should be marked as nice as part of access
     *
     * @return true if the operation was successfully carried out;
     * false if NoWait locking was requested and the page lock could
     * not be acquired
     */
    bool testOp(OpType opType, uint iPage, bool bNice);

    /**
     * Makes up an operation name based on an OpType.
     */
    char const *getOpName(OpType opType);

    /**
     * Gets the LockMode corresponding to an OpType.
     */
    LockMode getLockMode(OpType opType);

    /**
     * Carries out an operation on each disk page in order from
     * 0 to nDiskPages-1.
     *
     * @param opType see testOp
     */
    void testSequentialOp(OpType opType);

    /**
     * Carries out an operation on nRandomOps pages selected at random.
     *
     * @param opType see testOp
     */
    void testRandomOp(OpType opType);

    /**
     * Carries out an operation on every "n" pages, starting at page 0
     *
     * @param opType see testOp
     *
     * @param n the offset between each page
     */
    void testSkipOp(OpType opType, uint n);

    /**
     * Performs nRandomOps scratch operations.  A scratch operation
     * consists of locking a scratch page, filling it with random
     * data, and then unlocking it.
     */
    void testScratch();

    /**
     * Performs a limited number of prefetch operations.  Prefetches
     * are not verified.
     */
    void testPrefetch();

    /**
     * Performs a limited number of batch prefetch operations.  Prefetches
     * are not verified.
     */
    void testPrefetchBatch();

    /**
     * Performs a periodic checkpoint.
     */
    virtual void testCheckpoint();

    /**
     * Initializes all disk pages, filling them with information based
     * on their block numbers.
     */
    virtual void testAllocateAll();

    /**
     * Carries out one sequential read pass over the entire device.
     */
    void testSequentialRead();

    /**
     * Carries out one sequential write pass over the entire device.
     */
    void testSequentialWrite();

    /**
     * Carries out nRandomOps read operations on pages selected at random.
     */
    void testRandomRead();

    /**
     * Carries out nRandomOps write operations on pages selected at random.
     */
    void testRandomWrite();

    /**
     * Carries out write operations every n pages
     *
     * @param n offset between pages
     */
    void testSkipWrite(uint n);

    virtual void testAllocate();

    virtual void testDeallocate();

    void testCheckpointGuarded();

    void testCacheResize();

    /**
     * Carries out specified tests in multi-threaded mode.
     */
    void testMultipleThreads();

    virtual void threadInit();

    virtual void threadTerminate();

    virtual bool testThreadedOp(int iOp);
};

FENNEL_END_NAMESPACE

#endif

// End PagingTestBase.h
