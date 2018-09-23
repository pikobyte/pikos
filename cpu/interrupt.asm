;
; PikOS
; interrupt.asm
;
; Defines the general interrupt functions and provides an implementation for
; each. Every interrupt is passed to a common function where the CPU is saved,
; its data sent to the C handling function, and then restored. Not all of the
; interrupts send an error code, so a dummy byte is pushed for those who do
; not.

; Common ISR code
isr_common:
	pusha               ; Pushes general purpose registers
	mov ax, ds          ; Move DS into the lower 16-bits of EAX
	push eax            ; Save the data segment descriptor
	mov ax, 0x10        ; Copy the kernel data segment descriptor into AX
	mov ds, ax          ; and then to all segment registers
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	call isr_handler    ; Call the C handling function
	
	pop eax             ; Restore the general purpose registers
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax          ; Restore the segment registers
	popa
	add esp, 8          ; Clean up the pushed error code and pushed ISR number
	sti
	iret                ; Interrupt return, pops CS, EIP, EFLAGS, SS, and ESP


; Define the C handling function.
[extern isr_handler]


; Define all of the interrupt functions.
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; 0: Divide By Zero Exception
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common

; 1: Debug Exception
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common

; 3: Int 3 Exception
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common

; 4: INTO Exception
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common

; 5: Out of Bounds Exception
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common

; 6: Invalid Opcode Exception
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common

; 7: Co-processor Not Available Exception
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common

; 8: Double Fault Exception (with error code)
isr8:
    cli
    push byte 8
    jmp isr_common

; 9: Co-processor Segment Overrun Exception
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common

; 10: Bad TSS Exception (with error code)
isr10:
    cli
    push byte 10
    jmp isr_common

; 11: Segment Not Present Exception (with error code)
isr11:
    cli
    push byte 11
    jmp isr_common

; 12: Stack Fault Exception (with error code)
isr12:
    cli
    push byte 12
    jmp isr_common

; 13: General Protection Fault Exception (with error code)
isr13:
    cli
    push byte 13
    jmp isr_common

; 14: Page Fault Exception (with error code)
isr14:
    cli
    push byte 14
    jmp isr_common

; 15: Reserved Exception
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common

; 16: Floating Point Exception
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common

; 17: Alignment Check Exception
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common

; 18: Machine Check Exception
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common

; 19: Reserved
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common

; 20: Reserved
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common

; 21: Reserved
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common

; 22: Reserved
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common

; 23: Reserved
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common

; 24: Reserved
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common

; 25: Reserved
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common

; 26: Reserved
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common

; 27: Reserved
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common

; 28: Reserved
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common

; 29: Reserved
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common

; 30: Reserved
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common

; 31: Reserved
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common