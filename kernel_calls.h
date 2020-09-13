#ifndef _kernel_calls_h
#define _kernel_calls_h

extern void  svc_kprintf(const char *fmt, ... );
extern Item  svc_createitem(int32 ctype,TagArg *p);
extern Err   svc_deleteitem(Item i);
extern Item  svc_finditem(int32 ctype,TagArg *tp);
extern Err   svc_closeitem(Item i);
extern Item  svc_openitem(Item foundItem, void *args);
extern int32 svc_setitempri(Item i,uint8 newpri);
extern Err   svc_setitemowner(Item i,Item newOwner);
extern int32 svc_lockitem(Item s,uint32 flags);
extern Err   svc_unlockitem(Item s);
extern Item  svc_findandopenitem(int32 ctype,TagArg *tp);


extern Node *svc_remhead(List *l);
extern Node *svc_remtail(List *l);
extern void svc_addtail(List *l, Node *n);
extern void svc_addhead(List *l, Node *n);
extern void svc_removenode( Node *n);
extern void svc_initlist(List *l, const char *name);
extern Node *svc_findnamednode(const List *l, const char *name);
extern void svc_inserttail(List *l, Node *n);

extern void *svc_allocmem(int32 size, uint32 memflags);
extern void svc_freemem(void *p, int32 size);
extern int32 svc_scavengemem(void);
extern void svc_memset(void *dest, int32 value, int32 size);
extern void svc_memcpy(void *dest, void *src, int32 size);
extern int32 svc_getpagesize(uint32 typebits);

extern void *svc_locateitem(Item i);


#endif
