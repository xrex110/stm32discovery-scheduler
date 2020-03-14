.cpu cortex-m0
.thumb
.syntax unified
.fpu softvfp

.global context_switch
context_switch:
	//Accepts two arguments, the stack pointer of the
	//process to context switch out, and the stack pointer
	//of the process to context switch in
	//r0 = &prstackptr of old, r1 = &prstackptr of new

	//Save the link reg into prslinkreg of old proc
	//Gotta also save flags at some point
	//push {apsr}s
	push {r4-r7, lr}
	//ldr r4, [sp, #40]	//get &prlinkreg
	mov r2, sp
	str r2, [r0]	//Store stack pointer into &prstackptr

	//Okay, so now in r1 we have &prstackptr of new
	ldr r2, [r1]	//Get stack ptr for new proc
	mov sp, r2		//Move stack ptr for new proc into sp
	pop {r4-r7, pc}
