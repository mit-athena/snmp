/*
 * This is the MIT supplement to the PSI/NYSERNet implementation of SNMP.
 * This file describes the RPC (Remote Procedure Call) portion of the mib.
 *
 * Copyright 1990 by the Massachusetts Institute of Technology.
 *
 * For copying and distribution information, please see the file
 * <mit-copyright.h>.
 *
 * Tom Coppeto
 * MIT Network Services
 * 15 April 1990
 *
 *    $Source: /afs/dev.mit.edu/source/repository/athena/etc/snmp/server/src/rpc_grp.c,v $
 *    $Author: tom $
 *    $Locker:  $
 *    $Log: not supported by cvs2svn $
 * Revision 1.2  90/04/26  17:56:42  tom
 * *** empty log message ***
 * 
 *
 */

#ifndef lint
static char *rcsid = "$Header: /afs/dev.mit.edu/source/repository/athena/etc/snmp/server/src/rpc_grp.c,v 1.3 1990-05-26 13:40:27 tom Exp $";
#endif

#include "include.h"
#include <mit-copyright.h>

#ifdef MIT
#ifdef RPC


/* 
 * rpc stats structs
 */

struct 
{
  int calls;
  int badcalls;
  int retrans;
  int badxids;
  int timeouts;
  int waits;
  int newcreds;
} rcl;


struct 
{
  int calls;
  int badcalls;
  int nullrecv;
  int badlen;
  int xdrcall;
} rsv;



/*
 * Function:    lu_rpccl()
 * Description: Top level callback for RPC. Supports client side RPC stats.
 * Returns:     BUILD_ERR/BUILD_SUCCESS
 */

int
lu_rpccl(varnode, repl, instptr, reqflg)
     struct snmp_tree_node *varnode;
     varbind *repl;
     objident *instptr;
     int reqflg;
{

  if (varnode->flags & NOT_AVAIL ||
      varnode->offset <= 0 ||     /* not expecting offset here */
      ((varnode->flags & NULL_OBJINST) && (reqflg == NXT)))
    return (BUILD_ERR);

  if(nl[N_RCSTAT].n_value == 0 )
    {
      syslog(LOG_WARNING, "lu_rpccl: can't get namelists for rpc");
      return(BUILD_ERR);
    }
  
  if(lseek(kmem, (long) nl[N_RCSTAT].n_value, L_SET) != nl[N_RCSTAT].n_value)
    {
     syslog(LOG_WARNING, "lu_rpccl: can't lseek");
     return(BUILD_ERR);
    }
  
  if(read(kmem, &rcl, sizeof(rcl)) != sizeof(rcl))
    {
      syslog(LOG_WARNING, "lu_rpccl: can't read cl");
      return(BUILD_ERR);
    }

  /*
   * Build reply
   */

  bcopy ((char *)varnode->var_code, (char *) &repl->name, sizeof(repl->name));
  repl->name.ncmp++;                    /* include the "0" instance */

  repl->val.type = CNTR;  /* True of all the replies */

  switch (varnode->offset) 
    {
    case N_RPCCCALL:
      repl->val.value.cntr = rcl.calls;
      return (BUILD_SUCCESS);
    case N_RPCCBADCALL:
      repl->val.value.cntr = rcl.badcalls;
      return (BUILD_SUCCESS);
    case N_RPCCRETRANS:
      repl->val.value.cntr = rcl.retrans;
      return (BUILD_SUCCESS);
    case N_RPCCBADXID:
      repl->val.value.cntr = rcl.badxids;
      return (BUILD_SUCCESS);
    case N_RPCCTIMEOUT:
      repl->val.value.cntr = rcl.timeouts;
      return (BUILD_SUCCESS);
    case N_RPCCWAIT:
      repl->val.value.cntr = rcl.waits;
      return (BUILD_SUCCESS);
    case N_RPCCNEWCRED:
      repl->val.value.cntr = rcl.newcreds;
      return (BUILD_SUCCESS);
    default:
      syslog (LOG_ERR, "lu_rpccl: bad rpc offset: %d", varnode->offset);
      return(BUILD_ERR);
  }
}



/*
 * Function:    lu_rpcsv()
 * Description: Top level callback for RPC. Supports server side RPC stats.
 * Returns:     BUILD_ERR/BUILD_SUCCESS
 */

lu_rpcsv(varnode, repl, instptr, reqflg)
     struct snmp_tree_node *varnode;
     varbind *repl;
     objident *instptr;
     int reqflg;
{

  if (varnode->flags & NOT_AVAIL ||
      varnode->offset <= 0 ||     /* not expecting offset here */
      ((varnode->flags & NULL_OBJINST) && (reqflg == NXT)))
    return (BUILD_ERR);

  if(nl[N_RSSTAT].n_value == 0 )
    {
      syslog(LOG_WARNING, "lu_rpcsv: can't get namelists for rpc");
      return(BUILD_ERR);
    }
  
  if(lseek(kmem, (long) nl[N_RSSTAT].n_value, L_SET) != nl[N_RSSTAT].n_value)
    {
     syslog(LOG_WARNING, "lu_rpcsv: can't lseek");
     return(BUILD_ERR);
    }
  
  if(read(kmem, &rsv, sizeof(rsv)) != sizeof(rsv))
    {
      syslog(LOG_WARNING, "lu_rpcsv: can't read cl");
      return(BUILD_ERR);
    }

  /*
   * Build reply
   */

  bcopy ((char *)varnode->var_code, (char *) &repl->name, sizeof(repl->name));
  repl->name.ncmp++;                    /* include the "0" instance */

  repl->val.type = CNTR;  /* True of all the replies */

  switch (varnode->offset) 
    {
    case N_RPCSCALL:
      repl->val.value.cntr = rsv.calls;
      return (BUILD_SUCCESS);
    case N_RPCSBADCALL:
      repl->val.value.cntr = rsv.badcalls;
      return (BUILD_SUCCESS);
    case N_RPCSNULLRECV:
      repl->val.value.cntr = rsv.nullrecv;
      return (BUILD_SUCCESS);
    case N_RPCSBADLEN:
      repl->val.value.cntr = rsv.badlen;
      return (BUILD_SUCCESS);
    case N_RPCSXDRCALL:
      repl->val.value.cntr = rsv.xdrcall;
      return (BUILD_SUCCESS);
    default:
      syslog (LOG_ERR, "lu_rpcsv: bad rpc offset: %d", varnode->offset);
      return(BUILD_ERR);
  }
}


#endif RPC
#endif MIT
