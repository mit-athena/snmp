/*
 * This is the MIT supplement to the PSI/NYSERNet implementation of SNMP.
 * This file describes the Mail service portion of the mib.
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
 *    $Source: /afs/dev.mit.edu/source/repository/athena/etc/snmp/server/src/mail_grp.c,v $
 *    $Author: tom $
 *    $Locker:  $
 *    $Log: not supported by cvs2svn $
 * Revision 1.4  90/05/26  13:38:30  tom
 * athena release 7.0e
 * 
 * Revision 1.3  90/04/26  17:05:15  tom
 * added rcsid
 * 
 * Revision 1.2  90/04/26  17:04:06  tom
 * *** empty log message ***
 * 
 *
 */

#ifndef lint
static char *rcsid = "$Header: /afs/dev.mit.edu/source/repository/athena/etc/snmp/server/src/mail_grp.c,v 2.0 1992-04-22 02:02:12 tom Exp $";
#endif

#include "include.h"
#include <mit-copyright.h>

#ifdef MIT

#include <sys/dir.h>

/*
 * Mail queue directory
 */


static int crock_mailq();


/* 
 * Function:    lu_mail()
 * Decsription: Top level callback for mail. Supports the following:
 *              N_MAILQUEUE- (INT) size of mail queue
 * Returns:     BUILD_ERR/BUILD_SUCCESS
 */ 

int
lu_mail(varnode, repl, instptr, reqflg)
     struct snmp_tree_node *varnode;
     varbind *repl;
     objident *instptr;
     int reqflg;
{
  if (varnode->flags & NOT_AVAIL ||
      varnode->offset < 0 ||     /* not expecting offset here */
      ((varnode->flags & NULL_OBJINST) && (reqflg == NXT)))
    return (BUILD_ERR);

  /*
   * Build reply
   */

  bcopy ((char *)varnode->var_code, (char *) &repl->name, sizeof(repl->name));
  repl->name.ncmp++;                    /* include the "0" instance */
  repl->val.type = INT;
  if((repl->val.value.intgr = crock_mailq()) != BUILD_SUCCESS)
    return(BUILD_ERR);
  return(BUILD_SUCCESS);
}


/* 
 * Function:    crock_mailq()
 * Decsription: Counts number of qfa files in mail queue directory.
 * Returns:     Number of files if successful
 *              BUILD_ERR if failure
 */
 

static int
crock_mailq()
{
  DIR *d;
#ifdef POSIX
  struct dirent *dp;
#else
  struct direct *dp;
#endif
  int count = 0;

  d = opendir(mail_q);
  if(d == (DIR *) NULL)
    {
      syslog(LOG_WARNING, "lu_mail: cannot open %s", mail_q);
      return(BUILD_ERR);
    }

  while(dp = readdir(d))
    if(strncmp(dp->d_name, "qf", 2) == 0)
      ++count;

  closedir(d);
  return(count);
}

#endif MIT
