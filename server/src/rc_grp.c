/* Copyright MIT */

#include "include.h"

#define MAX_REPLY_SIZE 32


lu_rcvar(varnode, repl, instptr, reqflg)
     struct snmp_tree_node *varnode;
     varbind *repl;
     objident *instptr;
     int reqflg;
{
  if (varnode->flags & NOT_AVAIL ||
      varnode->offset <= 0 ||
      ((varnode->flags & NULL_OBJINST) && (reqflg == NXT)))
    return (BUILD_ERR);

  
  /*
   * Build reply
   */

  bcopy ((char *)varnode->var_code, (char *) &repl->name, sizeof(repl->name));
  repl->name.ncmp++;			/* include the "0" instance */

  repl->val.type = STR;  /* True of all the replies */
  repl->val.value.str.str = (char *) malloc(sizeof(char) * MAX_REPLY_SIZE);
  repl->val.value.str.len = MAX_REPLY_SIZE;

  switch (varnode->offset) 
    {
    case N_RCHOST:
      get_variable("HOST",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCADDR:
      get_variable("ADDR",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCMACHINE:
      get_variable("MACHINE",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCSYSTEM:
      get_variable("SYSTEM",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCWS:
      get_variable("WS",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCTOEHOLD:
      get_variable("TOEHOLD",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCPUBLIC:
      get_variable("PUBLIC",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCERRHALT:
      get_variable("ERRHALT",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCLPD:
      get_variable("LPD",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCRVDSRV:
      get_variable("RVDSRV",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCRVDCLIENT:
      get_variable("RVDCLIENT",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCNFSSRV:
      get_variable("NFSSRV",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCNFSCLIENT:
      get_variable("NFSCLIENT",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCAFSSRV:
      get_variable("AFSCLIENT",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCRPC:
      get_variable("RPC",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCSAVECORE:
      get_variable("SAVECORE",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCPOP:
      get_variable("POP",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCSENDMAIL:
      get_variable("SENDMAIL",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCQUOTAS:
      get_variable("QUOTAS",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCACCOUNT:
      get_variable("ACCOUNT",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCOLC:
      get_variable("OLC",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCTIMESRV:
      get_variable("TIMESRV",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCPCNAMED:
      get_variable("PCNAMED",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCNEWMAILCF:
      get_variable("NEWMAILCF",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCKNETD:
      get_variable("KNETD",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCTIMEHUB:
      get_variable("TIMEHUB",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCZCLIENT:
      get_variable("ZCLIENT",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCZSERVER:
      get_variable("ZSERVER",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCSMSUPDATE:
      get_variable("SMSUPDATE",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCINETD:
      get_variable("INETD",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCNOCREATE:
      get_variable("NOCREATE",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    case N_RCNOATTACH:
      get_variable("NOATTACH",repl->val.value.str.str,MAX_REPLY_SIZE);
      return(BUILD_SUCCESS);
    }
}


get_variable(var,string,size)
  char *var;
  char *string;
  int size;
{
  char *ptr;

  ptr = (char *) getenv(var);
  strncpy(string,ptr,size);
  string[size-1] = '\0';
}