.cpu cortex-m0
.thumb
.syntax unified
.fpu softvfp

.global ctx_sw_a
ctx_sw_a:
	push {r4-r7, lr}
	movs r4, #4
	movs r5, #5
	movs r6, #6
	movs r7, #7

	ldr r0, =a_str1
	bl printf

//ctw_sw

	pop {r4-r7, pc}

a_str1:
	.string "preparing to context switch...\n"
	.align 2

a_str:
	.string ""
	.align 2

.global ctx_sw_a
ctx_sw_b:
	push {r4-r7, lr}
	movs r4, #8
	movs r5, #9
	movs r6, #10
	movs r7, #11

	pop {r4-r7, pc}

b_str1:
	.string "context'ed in b\n"
	.align 2
