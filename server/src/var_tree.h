/*
 * $Header: /afs/dev.mit.edu/source/repository/athena/etc/snmp/server/src/var_tree.h,v 1.2 1990-04-26 18:38:00 tom Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1  90/04/23  14:28:32  tom
 * Initial revision
 * 
 * Revision 1.1  89/11/03  15:43:34  snmpdev
 * Initial revision
 * 
 */

/*
 * THIS SOFTWARE IS THE CONFIDENTIAL AND PROPRIETARY PRODUCT OF PERFORMANCE
 * SYSTEMS INTERNATIONAL, INC. ANY UNAUTHORIZED USE, REPRODUCTION, OR TRANSFER 
 * OF THIS SOFTWARE IS STRICTLY PROHIBITED.  COPYRIGHT (C) 1990 PSI, INC.  
 * (SUBJECT TO LIMITED DISTRIBUTION AND RESTRICTED DISCLOSURE ONLY.) 
 * ALL RIGHTS RESERVED.
 */

/*
 * THIS SOFTWARE IS THE CONFIDENTIAL AND PROPRIETARY PRODUCT OF NYSERNET,
 * INC.  ANY UNAUTHORIZED USE, REPRODUCTION, OR TRANSFER OF THIS SOFTWARE
 * IS STRICTLY PROHIBITED.  (C) 1989 NYSERNET, INC.  (SUBJECT TO 
 * LIMITED DISTRIBUTION AND RESTRICTED DISCLOSURE ONLY.)  ALL RIGHTS RESERVED.
 */

/*
 *  $Header: /afs/dev.mit.edu/source/repository/athena/etc/snmp/server/src/var_tree.h,v 1.2 1990-04-26 18:38:00 tom Exp $
 *
 *  June 28, 1988 - Mark S. Fedor
 *  Copyright (c) NYSERNet Incorporated, 1988, All Rights Reserved
 */

/*
 *  this file contains all the definitions which pertain to
 *  the SNMP variable tree and the SNMP variables.
 *  This file is included by "include.h".
 */

/*
 *  maximum children per tree node
 */

#define MAXCHILDPERNODE	64

/*
 *  this defines the constant prefix of the MIB variables.
 *  The constant prefix is:
 *
 *  iso(1) org(3) dod(6) internet(1)
 *
 *  The constant is so we can start the tree at the correct place
 *  and not have to traverse the first constant part of the tree.
 */

#define MIB_PREFIX_SIZE	4

/*
 *  definitions for snmp_tree_node flags
 */

#define LEAF_NODE	0x1		/* this is a leaf node of the tree */
#define PARENT_NODE	0x2		/* this is a parent node of tree */
#define NOT_AVAIL	0x4		/* requested variable not supported */
#define AGENT_VAR	0x8		/* this var is from a daemon */
#define GET_LEX_NEXT	0x10		/* this var is lexi-next */
#define NULL_OBJINST	0x20		/* this var has no object instance */
#define WRITE_VAR	0x40		/* this var is writable */
#define VAL_INT		0x80		/* variable value of integer */
#define VAL_STR		0x100		/* variable value of string */
#define VAL_OBJ		0x200		/* variable value of Object ID */
#define VAL_EMPTY	0x400		/* variable value of NULL */
#define VAL_IPADD	0x800		/* variable value of ip address */
#define VAL_CNTR	0x1000		/* variable value of counter */
#define VAL_GAUGE	0x2000		/* variable value of gauge */
#define VAL_TIME	0x4000		/* variable value of timeTicks */
#define VAL_OPAQUE	0x8000		/* variable value of opaque */

#define VAL_MASK (VAL_INT | VAL_STR | VAL_OBJ | VAL_EMPTY | VAL_IPADD | \
		  VAL_CNTR | VAL_GAUGE | VAL_TIME | VAL_OPAQUE )

/*
 *  definitions for agent packet types
 */

#define AGENT_REG	0x01		/* var registration from an agent */
#define AGENT_REQ	0x02		/* to request a var from an agent */
#define AGENT_ERR	0x03		/* error was encountered */
#define AGENT_RSP	0x04		/* response from an agent */

/*
 *  miscellaneous definitions
 */

#define CONNECT_FAIL	-1		/* addition of node to tree failed */
#define CONNECT_SUCCESS	0x2		/* addition of node to tree succeded */
#define BUILD_ERR	-4		/* error during var. tree building */
#define BUILD_SUCCESS	0x8		/* var. tree build was successful */

#define SNMPNODENULL	(struct snmp_tree_node *)NULL   /* makes lint happy */
#define SNMPINFONULL	(struct snmp_tree_info *)NULL   /* makes lint happy */

/*
 *  SNMP tree node structure, some of the types taken from
 *  <arpa/snmp/snmp.h>
 */
struct snmp_tree_node {
	int     (*getval)();	/* ptr to func to get value of SNMP variable */
	int     (*setval)();	/* ptr to func to set value of SNMP variable */
	off_t     offset;	/* kmem offset of SNMP variable */
	int       flags;	/* leaf? in kmem? static answer? */
	objident *var_code;	/* variable code as in RFC */
	struct sockaddr_in *from;      /* if an agent var, who is this from? */
	struct snmp_tree_node *child[MAXCHILDPERNODE+1]; /* ptr to children */
};

/*
 *  SNMP variable code and type size table structure
 *
 *  statically set with all the SNMP variables the UNIX snmpd
 *  will support.
 */

struct snmp_tree_info {
	objident  *codestr;		/* variable code number string */
	int   (*valfunc)();		/* ptr to funtion to get var value */
	int   (*valsetfunc)();		/* ptr to funtion to set var value */
	int	nl_def;			/* namelist definition for nl() */
	int	var_flags;		/* initial value for tree node flags */
};

/*
 *  Lookup indices for particular variables.
 */

/*
 *  Namelist defines.
 */

#define N_IFNET		0
#define N_IPSTAT	1
#define N_RTNET		2
#define N_RTHASH	3
#define N_RTSTAT	4
#define N_MBSTAT	5
#define N_ICMPSTAT	6
#define N_TCB		7
#define N_BOOT		8
#define N_RTHOST	9
#define N_TCPSTAT	10
#define N_UDPSTAT	11
#define N_IPFORWARD	12
#define N_ARPTAB	13
#define N_ARPSIZE	14

#ifdef MIT
#define N_AVENRUN       15
#define N_HZ            16 
#define N_CPTIME        17
#define N_RATE          18
#define N_TOTAL         19
#define N_DEFICIT       20
#define N_FORKSTAT      21
#define N_SUM           22
#define N_FIRSTFRE      23
#define N_MAXFREE       24
#define N_DKXFER        25
#define N_RECTIME       26
#define N_PGINTIME      27
#define N_PHZ           28
#define N_INTRNAM       29
#define N_EINTRNAM      30
#define N_INTCRNT       31
#define N_EINTCRNT      32
#define N_DKNDRIVE      33
#define N_XSTATS        34
#define N_INODE         35
#define N_XTEXT         36
#define N_PROC          37
#define N_CONS          38
#define N_FILE          39
#define N_USRPTMAP      40
#define N_USRPT         41
#define N_SWAPMAP       42
#define N_NPROC         43
#define N_NTEXT         44
#define N_NFILE         45
#define N_NINODE        46
#define N_NSWAPMAP      47
#define N_PTTTY         48
#define N_NPTY          49
#define N_DMIN          50
#define N_DMAX          51
#define N_NSWDEV        52
#define N_SWDEVT        53
#define N_REC           54
#define N_PGIN          55
#define N_SYSMAP        56
#ifdef VFS   
#define N_NCSTATS       57
#else  VFS
#define N_NCHSTATS      57
#endif VFS

#ifdef RPC
#define N_RCSTAT        58
#define N_RSSTAT        59
#endif RPC

#ifdef NFS
#define N_CLSTAT        60
#define N_SVSTAT        61
#endif NFS 

#ifdef VAX
#define N_MBDINIT       62
#define N_UBDINIT       63
#define N_DZTTY         64
#define N_DZCNT         65
#define N_DH11          66
#define N_NDH11         67
#endif vax

#ifdef ibm032      
#define N_IOCDINIT      62
#define N_ASY           63
#define N_NASY          64
#define N_PSP           65
#define N_NPSP          66
#endif ibm032
#endif MIT

/*
 *  Lookup defines.
 */

#define N_VERID		100
#define N_VEREV		101
#define N_LINIT		102
#define N_NNETS		103
#define N_IFMTU		104
#define N_IERRS		105
#define N_OERRS		106
#define N_SCOPE		107
#define N_IFTYP		108
#define N_IFSPD		109
#define N_IPKTS		110
#define N_OPKTS		111
#define N_INDEX		112
#define N_IPADD		113
#define N_IPIND		114
#define N_IPBRD		115
#define N_ICERR		116
#define N_DSTUN		117
#define N_TTLEX		118
#define N_IBHDR		119
#define N_SRCQE		120
#define N_IREDI		121
#define N_ECREQ		122
#define N_ECREP		123
#define N_ITIME		124
#define N_ITREP		125
#define N_MSKRQ		126
#define N_MSKRP		127
#define N_ORESP		128
#define N_OERRR		129
#define N_OSTUN		130
#define N_OTLEX		131
#define N_OBHDR		132
#define N_ORCQE		133
#define N_OREDI		134
#define N_OCREQ		135
#define N_OCREP		136
#define N_OTIME		137
#define N_OTREP		138
#define N_OSKRQ		139
#define N_OSKRP		140
#define N_IFSTA		141

#define N_RTDST		142
#define N_RTGAT		143
#define N_RTTYP		144
#define N_IFLCG		145
#define N_OQLEN		146
#define N_INMSG		147
#define N_IFATA		148

#define N_TSTE		149
#define N_LADD		150
#define	N_LPRT		151
#define N_FADD		152
#define N_FPRT		153

#define N_TMXCO		154
#define N_TACTO		155
#define N_TATFA		156
#define N_TESRE		157
#define N_TISEG		158
#define N_TOSEG		159
#define N_TRXMI		160

#define N_UIERR		161

#define N_TCEST		162
#define N_RTOAL		163
#define N_TRMI		164
#define N_TRMX		165

#define N_IPFDI		199
#define N_IPTTL		200
#define N_IPINR		201
#define N_IPHRE		202
#define N_IPADE		203
#define N_IPFOR		204
#define N_IPNOR		205
#define N_IPRTO		206
#define N_IPRAS		207
#define N_IPRFL		208

#define N_IPMSK		209

#define N_ARPA		220
#define N_AETH		221
#define N_AINDE		222

#define N_RTMT2		230
#define N_RTMT3		231
#define N_RTMT4		232

/**************** MIT *********************/

/*
 * Some of these definitions are redundant... since they only need to be 
 * unique within a callback. But this is easier for bookkeeping.
 */

#ifdef MIT
#ifdef ATHENA
#define N_MACHTYPE        240
#define N_MACHNDISPLAY    241
#define N_MACHDISPLAY     242
#define N_MACHNDISK       243
#define N_MACHDISK        244
#define N_MACHMEMORY      245

#define N_RCHOST          254
#define N_RCADDR      	  255
#define N_RCMACHINE   	  256
#define N_RCSYSTEM    	  257
#define N_RCWS        	  258
#define N_RCTOEHOLD   	  259
#define N_RCPUBLIC    	  260
#define N_RCERRHALT   	  261
#define N_RCLPD       	  262
#define N_RCRVDSRV    	  263
#define N_RCRVDCLIENT 	  264
#define N_RCNFSSRV    	  265
#define N_RCNFSCLIENT 	  266
#define N_RCAFSSRV    	  267
#define N_RCAFSCLIENT 	  268
#define N_RCRPC       	  269
#define N_RCSAVECORE  	  270
#define N_RCPOP       	  271
#define N_RCSENDMAIL  	  272
#define N_RCQUOTAS    	  273
#define N_RCACCOUNT   	  274
#define N_RCOLC       	  275
#define N_RCTIMESRV   	  276
#define N_RCPCNAMED   	  277
#define N_RCNEWMAILCF 	  278
#define N_RCKNETD     	  279
#define N_RCTIMEHUB   	  280
#define N_RCZCLIENT   	  281
#define N_RCZSERVER   	  282
#define N_RCSMSUPDATE 	  283
#define N_RCINETD     	  284
#define N_RCNOCREATE  	  285
#define N_RCNOATTACH  	  286

#define N_RELVERSION      287
#define N_RELDATE	  288		     
#endif ATHENA

#define N_STATTIME    	  289
#define N_STATLOAD    	  290
#define N_STATLOGIN       291

#define N_VMPROCR         292
#define N_VMPROCB	  293
#define N_VMPROCW	  294
#define N_VMMEMAVM	  295
#define N_VMMEMFRE	  296
#define N_VMPAGERE	  297
#define N_VMPAGEAT	  298
#define N_VMPAGEPN	  299
#define N_VMPAGEPO	  300
#define N_VMPAGEFR	  301
#define N_VMPAGEDE	  302
#define N_VMPAGESR	  303
#define N_VMMISCIN	  304
#define N_VMMISCSY	  305
#define N_VMMISCCS	  306
#define N_VMCPUUS	  307
#define N_VMCPUNI         308
#define N_VMCPUSY	  309
#define N_VMCPUID	  310
#define N_VMSWAPIN        311
#define N_VMSWAPOUT	  313
#define N_VMPGSWAPIN	  314
#define N_VMPGSWAPOUT	  315
#define N_VMATFAULTS	  316
#define N_VMPGSEQFREE	  317
#define N_VMPGREC	  318
#define N_VMPGFASTREC	  319
#define N_VMFLRECLAIM	  320
#define N_VMITBLKPGFAULT  321
#define N_VMZFPGCREATE	  322
#define N_VMZFPGFAULT	  323
#define N_VMEFPGCREATE	  324
#define N_VMEFPGFAULT     325
#define N_VMSTPGFRE	  326
#define N_VMITPGFRE	  327
#define N_VMFFPGCREATE	  328
#define N_VMFFPGFAULT	  329
#define N_VMPGSCAN	  330
#define N_VMCLKREV	  331
#define N_VMCLKFREE       332
#define N_VMCSWITCH	  333
#define N_VMDINTR	  334
#define N_VMSINTR	  335
#define N_VMTRAP	  336
#define N_VMSYSCALL       337
#if defined(vax)
#define N_VMPDMAINTR      338
#endif 
#define N_VMXACALL        339
#define N_VMXAHIT	  340
#define N_VMXASTICK	  341
#define N_VMXAFLUSH	  342
#define N_VMXAUNUSE	  343
#define N_VMXFRECALL	  344
#define N_VMXFREINUSE	  345
#define N_VMXFRECACHE	  346
#define N_VMXFRESWP	  347
#define N_VMFORK	  348
#define N_VMFKPAGE	  349
#define N_VMVFORK	  350
#define N_VMVFKPAGE	  351
#define N_VMRECTIME	  352
#define N_VMPGINTIME	  353
#ifdef VFS		  
#define N_VMNCSGOOD	  354
#define N_VMNCSBAD	  355
#define N_VMNCSFALSE	  356
#define N_VMNCSMISS	  357
#define N_VMNCSLONG       358
#define N_VMNCSTOTAL      359
#else  VFS
#define N_VMNCHGOOD       354
#define N_VMNCHBAD        355
#define N_VMNCHFALSE      356
#define N_VMNCHMISS       357
#define N_VMNCHLONG       358
#define N_VMNCHTOTAL      359
#endif VFS
			  
#define N_PSTOTAL         360
#define N_PSUSED          361
#define N_PSTUSED         362
#define N_PSFREE          363
#define N_PSWASTED	  364
#define N_PSMISSING	  365
#define N_PFTOTAL	  366
#define N_PFUSED	  367
#define N_PITOTAL	  368
#define N_PIUSED	  369
#define N_PIFREE          370
#define N_PPTOTAL	  371
#define N_PPUSED	  372
#define N_PTTOTAL	  373
#define N_PTUSED	  374
#define N_PTAVAIL         375
#define N_PTFREE          376
#define N_PTACTIVE        377
			  
#ifdef RPC		  
#define N_RPCCCALL        378
#define N_RPCCBADCALL     379
#define N_RPCCRETRANS     380
#define N_RPCCBADXID      381
#define N_RPCCTIMEOUT     382
#define N_RPCCWAIT        383
#define N_RPCCNEWCRED     384

#define N_RPCSCALL  	  385
#define N_RPCSBADCALL     386
#define N_RPCSNULLRECV    387
#define N_RPCSBADLEN      388
#define N_RPCSXDRCALL     389
#endif RPC

#ifdef NFS
#define N_NFSCCALL        390
#define N_NFSCBADCALL     391
#define N_NFSCNULL        392
#define N_NFSCGETADDR     393
#define N_NFSCSETADDR     394
#define N_NFSCROOT        395
#define N_NFSCLOOKUP      396
#define N_NFSCREADLINK    397
#define N_NFSCREAD        398
#define N_NFSCWRCACHE     399
#define N_NFSCWRITE       400
#define N_NFSCCREATE      401
#define N_NFSCREMOVE      402
#define N_NFSCRENAME      403
#define N_NFSCLINK        404
#define N_NFSCSYMLINK     405
#define N_NFSCMKDIR       406
#define N_NFSCRMDIR       407
#define N_NFSCREADDIR     408
#define N_NFSCFSSTAT      409
#define N_NFSCNCLGET      410
#define N_NFSCNCLSLEEP    411

#define N_NFSSCALL        412
#define N_NFSSBADCALL     413
#define N_NFSSNULL        414
#define N_NFSSGETADDR     415
#define N_NFSSSETADDR     416
#define N_NFSSROOT        417
#define N_NFSSLOOKUP      418
#define N_NFSSREADLINK    419
#define N_NFSSREAD        420
#define N_NFSSWRCACHE     421
#define N_NFSSWRITE       422
#define N_NFSSCREATE      423
#define N_NFSSREMOVE      424
#define N_NFSSRENAME      425
#define N_NFSSLINK        426
#define N_NFSSSYMLINK     427
#define N_NFSSMKDIR       428
#define N_NFSSRMDIR       429
#define N_NFSSREADDIR     430
#define N_NFSSFSSTAT      431
#endif NFS

#ifdef RVD

#define N_RVDCBADBLOCK    432
#define N_RVDCBADCKSUM	  433
#define N_RVDCBADTYPE	  434
#define N_RVDCBADSTATE	  435
#define N_RVDCBADFORMAT	  436
#define N_RVDCTIMEOUT	  437
#define N_RVDCBADNONCE	  438
#define N_RVDCERRORRECV   439
#define N_RVDCBADDATA	  440
#define N_RVDCBADVERS 	  441
#define N_RVDCPKTREJ	  442
#define N_RVDCPUSH	  443
#define N_RVDCPKTSENT	  444
#define N_RVDCPKTRECV	  445
#define N_RVDCQKRETRANS	  446
#define N_RVDCLGRETRANS	  447
#define N_RVDCBLOCKRD	  448
#define N_RVDCBLOCKWR	  449

#endif RVD		  
			  
#ifdef AFS
#define N_AFSCPRIMCELL    450
#define N_AFSCCACHESIZE   451
#define N_AFSCCACHEDIR    452
#endif AFS

#ifdef KERBEROS
#define N_KRBCREALM       453
#define N_KRBCKEY         454
#define N_KRBCSERVER      455
#endif KERBEROS

#ifdef ZEPHYR
#define N_ZCPVERSION      456
#define N_ZCSERVER        457
#define N_ZCQUEUE         458
#define N_ZCSERVCHANGE    459
#define N_ZCHEADER        460
#define N_ZCLOOKING       461
#define N_ZCUPTIME        462
#define N_ZCSIZE          463

#define N_ZSPVERSION      464
#define N_ZSHEADER        465
#define N_ZSHEADER        466
#define N_ZSPACKET        467
#define N_ZSUPTIME        468
#define N_ZSSTATE         469
#endif ZEPHYR

#define N_MAILALIAS       500
#define N_MAILALIASPAG    501
#define N_MAILALIASDIR    502
#define N_RPCCRED         503
#define N_RPCCREDPAG      504
#define N_RPCCREDDIR      505
#endif MIT
