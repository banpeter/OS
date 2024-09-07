# OS

SysTick 

	If the device implements the SysTick timer, a SysTick exception is
	generated when the SysTick timer reaches zero. Software can also
	generate a SysTick exception. In an OS environment, the processor can
	use this exception as system tick.

System handlers NMI, PendSV, SVCall, and SysTick are all system exceptions handled by
system handlers.


xPSR

	The processor saves an EXC_RETURN value to the LR on exception entry. The exception
	mechanism relies on this value to detect when the processor has completed an exception
	handler. Bits[31:4] of an EXC_RETURN value are 0xFFFFFFF. When the processor loads a value
	matching this pattern to the PC it detects that the operation is not a normal branch operation and,
	instead, that the exception is complete. As a result, it starts the exception return sequence.


The SVC instruction causes the SVC exception.
imm is ignored by the processor. If required, it can be retrieved by the exception handler
to determine what service is being requested.


This code is based on the piccolo-os project. I used this project to learn about operating system implementation(mainly context switching)
and about programing a microcontroller using C and arm assembly. 

Copyright (C) 2021-2022 Gary Sims
Copyright (C) 2022 Keith Standiford

Sources:

https://github.com/garyexplains/piccolo_os_v1.1/tree/main
	
