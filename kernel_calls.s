
        AREA |C$$code|, CODE, READONLY
|x$codeseg|

	EXPORT  svc_kprintf
	EXPORT  svc_createitem
	
	IMPORT KernelBase
	
svc_kprintf
	mov r12,#&0e
	b call_swi_in_r12
	
svc_createitem
	mov r12,#&0
	b call_swi_in_r12
		
		
		
		
	
	
	
call_swi_in_r12

	stmfd sp!, {r9,lr}
	ldr r9,=KernelBase
	ldr r9, [r9]
	ldrb lr, [r9, #&2a]
	add r12,r12,lr
	add r12,r12,#1
	mov lr,pc
	ldr pc,[r9,-r12,lsl#2]
	ldmfd sp!, {r9,pc}
	
	END
	
		
	
	
