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
#include "fennel/common/CommonPreamble.h"
#include "fennel/calculator/BoolInstruction.h"

FENNEL_BEGIN_CPPFILE("$Id$");

const char *
BoolOr::longName()
{
    return "BoolOr";
}

const char *
BoolOr::shortName()
{
    return "OR";
}

int
BoolOr::numArgs()
{
    return 3;
}

void
BoolOr::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolAnd::longName()
{
    return "BoolAnd";
}

const char *
BoolAnd::shortName()
{
    return "AND";
}

int
BoolAnd::numArgs()
{
    return 3;
}

void
BoolAnd::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolNot::longName()
{
    return "BoolNot";
}

const char *
BoolNot::shortName()
{
    return "NOT";
}

int
BoolNot::numArgs()
{
    return 2;
}

void
BoolNot::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolMove::longName()
{
    return "BoolMove";
}

const char *
BoolMove::shortName()
{
    return "MOVE";
}

int
BoolMove::numArgs()
{
    return 2;
}

void
BoolMove::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolRef::longName()
{
    return "BoolRef";
}

const char *
BoolRef::shortName()
{
    return "REF";
}

int
BoolRef::numArgs()
{
    return 2;
}

void
BoolRef::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolIs::longName()
{
    return "BoolIs";
}

const char *
BoolIs::shortName()
{
    return "IS";
}

int
BoolIs::numArgs()
{
    return 3;
}

void
BoolIs::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolIsNot::longName()
{
    return "BoolIsNot";
}

const char *
BoolIsNot::shortName()
{
    return "ISNOT";
}

int
BoolIsNot::numArgs()
{
    return 3;
}

void
BoolIsNot::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolEqual::longName()
{
    return "BoolEqual";
}

const char *
BoolEqual::shortName()
{
    return "EQ";
}

int
BoolEqual::numArgs()
{
    return 3;
}

void
BoolEqual::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolNotEqual::longName()
{
    return "BoolNotEqual";
}

const char *
BoolNotEqual::shortName()
{
    return "NE";
}

int
BoolNotEqual::numArgs()
{
    return 3;
}

void
BoolNotEqual::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolGreater::longName()
{
    return "BoolGreater";
}

const char *
BoolGreater::shortName()
{
    return "GT";
}

int
BoolGreater::numArgs()
{
    return 3;
}

void
BoolGreater::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolGreaterEqual::longName()
{
    return "BoolGreaterEqual";
}

const char *
BoolGreaterEqual::shortName()
{
    return "GE";
}

int
BoolGreaterEqual::numArgs()
{
    return 3;
}

void
BoolGreaterEqual::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolLess::longName()
{
    return "BoolLess";
}

const char *
BoolLess::shortName()
{
    return "LT";
}

int
BoolLess::numArgs()
{
    return 3;
}

void
BoolLess::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolLessEqual::longName()
{
    return "BoolLessEqual";
}

const char *
BoolLessEqual::shortName()
{
    return "LE";
}

int
BoolLessEqual::numArgs()
{
    return 3;
}

void
BoolLessEqual::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolIsNull::longName()
{
    return "BoolIsNull";
}

const char *
BoolIsNull::shortName()
{
    return "ISNULL";
}

int
BoolIsNull::numArgs()
{
    return 2;
}

void
BoolIsNull::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolIsNotNull::longName()
{
    return "BoolIsNotNull";
}

const char *
BoolIsNotNull::shortName()
{
    return "ISNOTNULL";
}

int
BoolIsNotNull::numArgs()
{
    return 2;
}

void
BoolIsNotNull::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}


const char *
BoolToNull::longName()
{
    return "BoolToNull";
}

const char *
BoolToNull::shortName()
{
    return "TONULL";
}

int
BoolToNull::numArgs()
{
    return 1;
}

void
BoolToNull::describe(string& out, bool values) const {
    describeHelper(out, values, longName(), shortName(), mResult, mOp1, mOp2);
}

FENNEL_END_CPPFILE("$Id$");

// End BoolInstruction.cpp
