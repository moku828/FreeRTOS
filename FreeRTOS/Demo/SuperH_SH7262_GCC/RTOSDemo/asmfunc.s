.global start
.extern _main
.global _set_imask
.global _get_imask
.global _get_fpscr
.global _nop
.global _sleep
.global _set_vbr
.global _set_fpscr
.global _set_cr
.global _vPortSaveFlopRegisters
.global _vPortRestoreFlopRegisters
.global _end

.section .stack, "w"
	.align  4
	.space  65536
stack_base:

.section .reset, "ax"

start:
	MOV.L   __vect, R0
	LDC     R0, VBR
	MOV.L   _stack_base, SP
	MOV.L   ___bss_start__, R4
	MOV.L   ___bss_end__, R6
	SUB     R4, R6
	MOV     #0, R5
	MOV.L   __memset, R0
	JSR     @R0
	NOP
	MOV.L   __main, R0
	JSR     @R0
	NOP
loop:
	BRA     loop
	NOP

	.align  4
__memset:
	.long   _memset
___bss_start__:
	.long   __bss_start__
___bss_end__:
	.long   __bss_end__
__main:
	.long   _main
_stack_base:
	.long   stack_base
__vect:
	.long   _vect

.section .text, "ax"

_set_imask:
	MOV.L   __imask, R0
	SHLL2   R4
	SHLL2   R4
	AND     R0, R4
	NOT     R0, R0
	STC     SR, R1
	AND     R0, R1
	OR      R4, R1
	LDC     R1, SR
	RTS
	NOP
_get_imask:
	MOV.L   __imask, R0
	STC     SR, R1
	AND     R0, R1
	SHLR2   R1
	SHLR2   R1
	RTS
	MOV     R1, R0
_get_fpscr:
	RTS
	STS     FPSCR, R0
_nop:
	RTS
	NOP
_sleep:
	SLEEP
	NOP
	RTS
	NOP
_set_vbr:
	LDC     R4, VBR
	RTS
	NOP
_set_fpscr:
	LDS     R4, FPSCR
	RTS
	NOP
_set_cr:
	LDC     R4, SR
	RTS
	NOP

	.align  4
_end:
	.long   stack_base
__imask:
	.long   0x000000F0

.section .bss, "aw"

.section .vector, "ax"
	.align  4
_vect:
	.long   start					/* 0  Power-on reset PC */
	.long   stack_base				/* 1  Power-on reset SP */
	.long   start					/* 2  Manual reset PC */
	.long   stack_base				/* 3  Manual reset SP */
	.space  112
	.long   _vPortStartFirstTask	/* 32  TRAPA (Trap instruction (user vector)) */
	.long   _vPortYieldHandler		/* 33  TRAPA (Trap instruction (user vector)) */
	.space  564
	.long   _vPortPreemptiveTick	/* 175  CMI0 (Compare match timer - Channel 0) */
	.space  12
	.long   _MTU_Match				/* 179  TGI0A (Multifunction timer pulse unit 2 - Channel 0) */
	.space  532
