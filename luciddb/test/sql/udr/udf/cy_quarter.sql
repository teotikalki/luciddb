-- $Id$
set schema 'udftest';
set path 'udftest';


values applib.calendar_quarter(DATE'1896-1-11');
values applib.calendar_quarter(TIMESTAMP'2001-5-9 9:57:59');
values applib.calendar_quarter(DATE'1-1-1');

-- null parameters
values applib.calendar_quarter(cast(null as date));
values applib.calendar_quarter(cast(null as timestamp));

-- failures
values applib.calendar_quarter(TIMESTAMP'2 12:59:21');

-- create view with reference to applib.calendar_quarter
create view v1(fm, dateQ, tsQ) as
select fm, applib.calendar_quarter(datecol), applib.calendar_quarter(tscol)
from data_source;

select * from v1
order by 1;

-- in expressions
select v1.fm, applib.calendar_quarter(datecol) || applib.calendar_quarter(tscol) || dateQ
from data_source, v1
order by 1;

-- cleanup
drop view v1;
