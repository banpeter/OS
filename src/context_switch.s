.thumb
.syntax unified


/*Set PSP to the stack pointer then set control register so Thread mode uses PSP*/

.global setPSP
setPSP:
    msr psp, r0
    movs r0, #2
    msr control, r0
    isb
    mrs r0, control
    bx lr



.type isr_pendsv, %function
.global isr_pendsv
isr_pendsv:

   	mrs r0, psp

    subs	r0, #16
    stmia	r0!,{r4,r5,r6,r7}
    mov	r4, r8
    mov	r5, r9
    mov	r6, r10
    mov	r7, r11
    subs	r0, #32
    stmia	r0!,{r4,r5,r6,r7}
    subs	r0, #16

    /* Save current task's SP: */
    ldr	r2, =current_task
    /*ldr	r1, [r2]*/
    str	r0, [r2]

    /* Load next task's SP: */
    ldr	r2, =next_task
    ldr	r0, [r2]
    /*ldr	r0, [r1]*/

    ldmia	r0!,{r4,r5,r6,r7}
    mov	r8, r4
    mov	r9, r5
    mov	r10, r6
    mov	r11, r7
    ldmia	r0!,{r4,r5,r6,r7}
    msr psp, r0

    ldr r0, =0xFFFFFFFD

    bx	r0









