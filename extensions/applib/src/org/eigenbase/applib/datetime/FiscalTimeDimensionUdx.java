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
package org.eigenbase.applib.datetime;

import java.sql.*;


/**
 * Fiscal Time Dimension UDX - includes extra columns on top of those in regular
 * time dimension, although both use TimeDimensionInternal. TODO: separate out
 * the fiscal info in the internal helper so fiscal information isn't calculated
 * when it's not used
 *
 * @author Elizabeth Lin
 * @version $Id$
 */
public abstract class FiscalTimeDimensionUdx
{
    //~ Methods ----------------------------------------------------------------

    public static void execute(
        int startYear,
        int startMonth,
        int startDay,
        int endYear,
        int endMonth,
        int endDay,
        int fiscalYearStartMonth,
        PreparedStatement resultInserter)
        throws SQLException
    {
        TimeDimensionInternal tdi =
            new TimeDimensionInternal(
                startYear,
                startMonth,
                startDay,
                endYear,
                endMonth,
                endDay,
                fiscalYearStartMonth);
        tdi.Start();

        for (int rowCount = 0; rowCount <= tdi.getNumDays(); rowCount++) {
            // Year
            int year = tdi.getYear();

            // Days since the epoch (January 1, 1970)
            int julianDay = tdi.getJulianDay();

            // Month number (1=January)
            int month = tdi.getMonth();

            // Months since the epoch (January 1, 1970)
            int julianMonth = ((year - 1970) * 12) + month;

            // Day of month
            int date = tdi.getDayOfMonth();

            // Calendar quarter
            int quarter = ((month - 1) / 3) + 1;

            // Beginning of year
            int dayInYear = tdi.getDayOfYear();

            // Week number in month
            int weekNumInMonth = tdi.getWeekOfMonth();

            // Week number in year
            int week = tdi.getWeek();

            // Day of week
            int dayOfWeek = tdi.getDayOfWeek();

            String isWeekend;
            if ((dayOfWeek == 1) || (dayOfWeek == 7)) {
                isWeekend = "Y";
            } else {
                isWeekend = "N";
            }

            // insert data into row
            int column = 0;

            // TIME_KEY_SEQ
            resultInserter.setInt(++column, rowCount + 1);

            // TODO: Julian date here? TIME_KEY
            resultInserter.setDate(++column, tdi.getDate());

            // DAY_OF_WEEK
            resultInserter.setString(
                ++column,
                TimeDimensionInternal.getDayOfWeek(dayOfWeek - 1));

            // WEEKEND
            resultInserter.setString(++column, isWeekend);

            // DAY_NUMBER_IN_WEEK
            resultInserter.setInt(++column, dayOfWeek);

            // DAY_NUMBER_IN_MONTH
            resultInserter.setInt(++column, date);

            // DAY_NUMBER_IN_QUARTER
            resultInserter.setInt(++column, tdi.getDayOfQuarter());

            // DAY_NUMBER_IN_YEAR
            resultInserter.setInt(++column, dayInYear);

            // DAY_NUMBER_OVERALL
            resultInserter.setInt(++column, julianDay); //THIS IS IT (uh, what?)

            // DAYS_FROM_JULIAN = DAY_NUMBER_OVERALL + 2440588
            resultInserter.setInt(++column, julianDay + 2440588);

            // WEEK_NUMBER_IN_MONTH
            resultInserter.setInt(++column, weekNumInMonth);

            // WEEK_NUMBER_IN_QUARTER
            resultInserter.setInt(++column, tdi.getWeekOfQuarter());

            // WEEK_NUMBER_IN_YEAR
            resultInserter.setInt(++column, week);

            // WEEK_NUMBER_OVERALL
            resultInserter.setInt(++column, 1 + (julianDay / 7));

            // MONTH_NAME
            resultInserter.setString(
                ++column,
                TimeDimensionInternal.getMonthOfYear(month - 1));

            // MONTH_NUMBER_IN_QUARTER
            resultInserter.setInt(++column, ((month - 1) % 3) + 1);

            // MONTH_NUMBER_IN_YEAR
            resultInserter.setInt(++column, month);

            // MONTH_NUMBER_OVERALL
            resultInserter.setInt(++column, julianMonth);

            // QUARTER
            resultInserter.setInt(++column, quarter);

            // YEAR
            resultInserter.setInt(++column, year);

            // CALENDAR_QUARTER
            resultInserter.setString(
                ++column,
                CalendarQuarterUdf.getCalendarQuarter(quarter, year));

            // WEEK_START_DATE
            resultInserter.setDate(++column, tdi.getFirstDayOfWeekDate());

            // WEEK_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfWeekDate());

            // MONTH_START_DATE
            resultInserter.setDate(++column, tdi.getFirstDayOfMonthDate());

            // MONTH_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfMonthDate());

            // QUARTER_START_DATE
            resultInserter.setDate(++column, tdi.getFirstDayOfQuarterDate());

            // QUARTER_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfQuarterDate());

            // YEAR_START_DATE
            resultInserter.setDate(++column, tdi.getFirstDayOfYearDate());

            // YEAR_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfYearDate());

            // FISCAL_YEAR
            resultInserter.setInt(++column, tdi.getFiscalYear());

            // FISCAL_DAY_NUMBER_IN_QUARTER
            resultInserter.setInt(++column, tdi.getDayOfFiscalQuarter());

            // FISCAL_DAY_NUMBER_IN_YEAR
            resultInserter.setInt(++column, tdi.getDayOfFiscalYear());

            // FISCAL_WEEK_START_DATE
            resultInserter.setDate(
                ++column,
                tdi.getFirstDayOfFiscalWeekDate());

            // FISCAL_WEEK_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfFiscalWeekDate());

            // FISCAL_WEEK_NUMBER_IN_MONTH
            resultInserter.setInt(++column, tdi.getWeekOfFiscalMonth());

            // FISCAL_WEEK_NUMBER_IN_QUARTER
            resultInserter.setInt(++column, tdi.getWeekOfFiscalQuarter());

            // FISCAL_WEEK_NUMBER_IN_YEAR
            resultInserter.setInt(++column, tdi.getWeekOfFiscalYear());

            // FISCAL_MONTH_START_DATE
            resultInserter.setDate(++column, tdi.getFirstDayOfMonthDate());

            // FISCAL_MONTH_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfMonthDate());

            // FISCAL_MONTH_NUMBER_IN_QUARTER
            resultInserter.setInt(
                ++column,
                ((tdi.getFiscalMonth() - 1) % 3) + 1);

            // FISCAL_MONTH_NUMBER_IN_YEAR
            resultInserter.setInt(++column, tdi.getFiscalMonth());

            // FISCAL_QUARTER_START_DATE
            resultInserter.setDate(
                ++column,
                tdi.getFirstDayOfFiscalQuarterDate());

            // FISCAL_QUARTER_END_DATE
            resultInserter.setDate(
                ++column,
                tdi.getLastDayOfFiscalQuarterDate());

            // FISCAL_QUARTER_NUMBER_IN_YEAR
            resultInserter.setInt(++column, tdi.getFiscalQuarter());

            // FISCAL_YEAR_START_DATE
            resultInserter.setDate(++column, tdi.getFirstDayOfFiscalYearDate());

            // FISCAL_YEAR_END_DATE
            resultInserter.setDate(++column, tdi.getLastDayOfFiscalYearDate());

            // update row
            resultInserter.executeUpdate();

            // increment date
            tdi.increment();
        }
    }
}

// End FiscalTimeDimensionUdx.java
