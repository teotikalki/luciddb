/*
// $Id$
// Package org.eigenbase is a class library of database components.
// Copyright (C) 2004-2004 Disruptive Tech
// Copyright (C) 2004-2004 John V. Sichi.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
package org.eigenbase.sql;

/**
 * SqlNewOperator represents an SQL <code>new specification</code> such as
 * <code>NEW UDT(1, 2)</code>.  When used in an SqlCall, SqlNewOperator takes a
 * single operand, which is an invocation of the constructor method; but when
 * used in a RexCall, the operands are the initial values to be used
 * for the new instance.
 *
 * @author John V. Sichi
 * @version $Id$
 */
public class SqlNewOperator extends SqlPrefixOperator
{
    public SqlNewOperator()
    {
        super("NEW", SqlKind.NewSpecification, 0, null, null, null);
    }
    
    // override SqlOperator
    public SqlNode rewriteCall(
        SqlCall call)
    {
        // New specification is purely syntactic, so we rewrite it as a
        // direct call to the constructor method.
        return call.getOperands()[0];
    }
}

// End SqlNewOperator.java