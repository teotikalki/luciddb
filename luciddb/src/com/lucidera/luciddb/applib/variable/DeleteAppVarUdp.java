/*
// $Id$
// Farrago is an extensible data management system.
// Copyright (C) 2006-2006 LucidEra, Inc.
// Copyright (C) 2006-2006 The Eigenbase Project
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version approved by The Eigenbase Project.
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
package com.lucidera.luciddb.applib.variable;

import net.sf.farrago.catalog.*;

import net.sf.farrago.cwm.core.*;
import net.sf.farrago.cwm.instance.*;

import com.lucidera.luciddb.applib.resource.*;

/**
 * SQL-invocable procedure to delete an application variable or context.
 *
 * @author John V. Sichi
 * @version $Id$
 */
public abstract class DeleteAppVarUdp
{
    public static void execute(String contextId, String varId)
    {
        FarragoRepos repos = null;
        boolean rollback = true;
        try {
            repos = AppVarUtil.getRepos();
            repos.beginReposTxn(true);
            CwmExtent context = AppVarUtil.lookupContext(repos, contextId);
            if (varId == null) {
                context.refDelete();
            } else {
                CwmTaggedValue tag = AppVarUtil.lookupVariable(
                    repos, context, varId);
                tag.refDelete();
            }
            rollback = false;
        } catch (Throwable ex) {
            throw ApplibResourceObject.get().AppVarWriteFailed.ex(
                contextId, varId, ex);
        } finally {
            if (repos != null) {
                repos.endReposTxn(rollback);
            }
        }
    }
}

// End DeleteAppVarUdp.java