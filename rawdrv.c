
#include "portfolio.h"
#include "kernel_calls.h"




enum driver_tags
{
        CREATEDRIVER_TAG_ABORTIO = TAG_ITEM_LAST+1,		//a
        CREATEDRIVER_TAG_MAXCMDS,						//b
        CREATEDRIVER_TAG_CMDTABLE,						//c
        CREATEDRIVER_TAG_MSGPORT,						//d
        CREATEDRIVER_TAG_INIT,							//e
        CREATEDRIVER_TAG_DISPATCH						//f
};

enum device_tags
{
        CREATEDEVICE_TAG_DRVR = TAG_ITEM_LAST+1,					//a
        CREATEDEVICE_TAG_CRIO,          /* createIO routine */		//b
        CREATEDEVICE_TAG_DLIO,          /* deleteIO routine */		//c
        CREATEDEVICE_TAG_OPEN,          /* open routine */			//d
        CREATEDEVICE_TAG_CLOSE,         /* close routine */			//e
        CREATEDEVICE_TAG_IOREQSZ,       /* optional request size */	//f
        CREATEDEVICE_TAG_INIT           /* InitRoutine to call */	//10
};



void drv_abortio(struct IOReq * ior);
//int32 drv_dispatch(struct IOReq * ior);
Item drv_init(struct Driver * drv);
//int32 drv_cmdtable(struct IOReq * ior);

int32 dev_init(struct Device * dev);
int32 dev_open(struct Device * dev);
void dev_close(struct Device * dev);

int32 drv_cmdwrite(struct IOReq * ior);
int32 drv_cmdread(struct IOReq * ior);
int32 drv_cmdstatus(struct IOReq * ior);

void * cmdtable[3]={
		(void*)drv_cmdwrite,
		(void*)drv_cmdread,
		(void*)drv_cmdstatus
};

volatile Item GlobalDeviceItem;

static TagArg tags_drv[]={
	{TAG_ITEM_PRI,(void*)1},					//0
	{TAG_ITEM_NAME,(void*)"rawdriver"},					//1
	{CREATEDRIVER_TAG_ABORTIO,(void*)drv_abortio},		//2
	{CREATEDRIVER_TAG_MAXCMDS,(void*)3},		//3
	{CREATEDRIVER_TAG_CMDTABLE,(void*)cmdtable},		//4
	{CREATEDRIVER_TAG_INIT,(void*)drv_init},			//5
	{TAG_END,(void*)0}						
};
static TagArg tags_dev[]={
	{TAG_ITEM_PRI,(void*)0x96},				//0
	{CREATEDEVICE_TAG_DRVR,(void*)1},			//1
	{TAG_ITEM_NAME,(void*)"raw"},					//2
	{CREATEDEVICE_TAG_INIT,(void*)dev_init},			//3
	{CREATEDEVICE_TAG_OPEN,(void*)dev_open},			//4
	{CREATEDEVICE_TAG_CLOSE,(void*)dev_close},			//5
	{TAG_END,(void*)0}
};

int main()
{
	Item drv;
	Item dev;
	int32 signal;
	int32 rxsignal;
	
	int32 rd1;

    Debug();
	kprintf("rawmem start %s\n",__DATE__);
	
	drv=CreateItem(MKNODEID(KERNELNODE,DRIVERNODE),tags_drv);

					
	if(drv<=0)
	{
		kprintf("Create driver failed %x\n",drv);
		PrintfSysErr(drv);
		return 0;
	}else{
		kprintf("Driver Item %x\n",drv);
	}


	tags_dev[1].ta_Arg=(void*)drv;

			
	if(dev<=0){
		kprintf("Create device failed %x\n",dev);
		PrintfSysErr(dev);
		return 0;
	}

	kprintf("Drv %x\n",drv);
	kprintf("Dev %x\n",dev);

	GlobalDeviceItem=dev;

	signal=AllocSignal(0);
	if(signal<=0){
		kprintf("Unable to alloc signal");
		return 0;
	}


	kprintf("Entering loop\n");
	do{
		rxsignal=WaitSignal(signal);
		if(rxsignal&SIGF_ABORT){
			kprintf("SIGF_ABORT\n");
			return 0;
		}else
		{
			kprintf("Got signal %x\n",rxsignal);
		}

	}while(1);


	kprintf("Out of loop\n");

	return 0;
}


void drv_abortio(struct IOReq * ior)
{
	svc_kprintf("PRIV drv_abortio\n");
}

Item drv_init(struct Driver * drv)
{
	svc_kprintf("PRIV drv_init\n");
	return drv->drv.n_Item;
}

int32 drv_cmdwrite(struct IOReq * ior)
{
	uint32 addr=ior->io_Info.ioi_CmdOptions;
	uint32 * data=(void*)ior->io_Info.ioi_Send.iob_Buffer;
	
	*(uint32*)addr=*data;

	return 1;
}
int32 drv_cmdread(struct IOReq * ior)
{
	uint32 addr=ior->io_Info.ioi_CmdOptions;
	uint32 * data=(void*)ior->io_Info.ioi_Recv.iob_Buffer;
	
	*data=*(uint32*)addr;
	
	return 1;
}
int32 drv_cmdstatus(struct IOReq * ior)
{
	return 0;
}

int32 dev_init(struct Device * dev)
{
	svc_kprintf("priv dev_init \n");
	return dev->dev.n_Item;
}
int32 dev_open(struct Device * dev)
{
	svc_kprintf("priv dev_open \n");
	return dev->dev.n_Item;
}
void dev_close(struct Device * dev)
{
	svc_kprintf("priv dev_close \n");
}
