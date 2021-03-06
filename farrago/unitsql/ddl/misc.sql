-- $Id$
-- Miscellaneous DDL

create schema misc;
set schema 'misc';
set path 'misc';

-- Table with description
create table table_with_desc (i int primary key) description 'this is a table';

-- should fail:  a table may not have multiple primary keys
create table dup_pk(i int not null primary key,j int not null primary key);

-- should fail:  duplicate constraint names
create table dup_constraints(
    i int not null constraint charlie primary key,
    j int not null constraint charlie unique);

-- test schema-wide index name uniqueness

create table t1(i int not null primary key)
create index xxx on t1(i);

-- should fail
create table t2(i int not null primary key)
create index xxx on t2(i);

-- likewise for constraint name uniqueness

create table t3(i int not null constraint lucy primary key);

-- should fail
create table t4(i int not null constraint lucy primary key);

-- test column uniqueness in index
create table t5(col1 int not null primary key, col2 int not null);
-- should be successful
create index i1 on t5(col1,col2);
-- should fail
create index i2 on t5(col1,col2,col1);

-- test column uniqueness error when index is a primary key constraint
-- should fail
create table t6(col1 int not null, col2 int not null, primary key(col1,col1));

-- FTRS-specific table validation rules

-- should fail:  FTRS tables cannot have multiple clustered indexes
create table dup_clustered(i int not null primary key,j int not null)
create clustered index ix on dup_clustered(i)
create clustered index ix2 on dup_clustered(j)
;

-- should fail:  FTRS tables must have a primary key
create table missing_pk(i int not null,j int not null);


-- FTRS support for create index on existing rows

create table t(
h int,
i int not null primary key,
j int, 
k int not null unique);

select k from t order by 1;

create index t_h on t(h);

select h from t order by 1;

insert into t values(1,1,1,1);
insert into t values(2,2,2,2);

select k from t order by 1;

select h from t order by 1;

create index t_j on t(j);

select j from t order by 1;

insert into t values(3,3,3,3);
insert into t values(4,4,4,4);

select h from t order by 1;

select k from t order by 1;

select j from t order by 1;

!set outputformat csv

explain plan for select k from t order by 1;

explain plan for select h from t order by 1;

explain plan for select j from t order by 1;

!set outputformat table


-- LCS-specific table validation rules

-- LCS tables don't require primary keys
create table lcs_table(i int not null)
server sys_column_store_data_server
;

-- verify creation of system-defined clustered index
!indexes LCS_TABLE

-- LCS tables may have multiple clustered indexes
create table lcs_table_explicit(i int not null,j int not null,k int not null)
server sys_column_store_data_server
create clustered index explicit_i on lcs_table_explicit(i)
create clustered index explicit_jk1 on lcs_table_explicit(j,k)
;

-- verify creation of user-defined clustered indexes
!indexes LCS_TABLE_EXPLICIT

-- should fail:  can't drop a clustered index
drop index explicit_jk1;

-- should fail: LCS clustered indexes may not overlap
create table lcs_table_overlap(i int not null,j int not null,k int not null)
server sys_column_store_data_server
create clustered index explicit_ij on lcs_table_overlap(i,j)
create clustered index explicit_jk2 on lcs_table_overlap(j,k)
;

-- test usage of UDT's for column type
create type square as (
    side_length double
) final;

create table lcs_table_udt(i int not null,s square)
server sys_column_store_data_server
;

-- test LCS drop/truncate
truncate table lcs_table;
drop table lcs_table_explicit;

-- test creation of unclustered index
create table lcs_table_unclustered(i int not null)
server sys_column_store_data_server
create index unclustered_i on lcs_table_unclustered(i)
;

-- test truncate of table with unclustered index
truncate table lcs_table_unclustered;

-- test drop of unclustered index
drop index unclustered_i;

-- test some features which aren't yet implemented for LCS

-- should fail:  can't handle collections yet
create table lcs_table_multiset(i int not null,im integer multiset)
server sys_column_store_data_server
;

-- should fail: can't drop primary key/unique indexes
create table testdrop(i1 int primary key, i2 int unique);
drop index "SYS$CONSTRAINT_INDEX$SYS$PRIMARY_KEY$TESTDROP";
drop index "SYS$CONSTRAINT_INDEX$SYS$UNIQUE_KEY$TESTDROP$I2";

-- End misc.sql
