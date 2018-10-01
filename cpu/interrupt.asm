;
; PikOS
; interrupt.asm
;
; Defines the general interrupt routines and provides an implementation for
; each. Every interrupt is passed to a common function where the CPU is saved,
; its data sent to the C handling function, and then restored. Not all of the
; interrupts send an error code, so a dummy byte is pushed for those who do
; not. We also handle interrupt requests (IRQs), where the programmable interrupt
; controller (PIC) has been remapped to the range 32-47.

; Common ISR function.
isr_common:
	  pusha            ; Pushes general purpose registers
	  mov   ax, ds     ; Move DS into the lower 16-bits of EAX
	  push  eax        ; Save the data segment descriptor
	  mov   ax, 0x10   ; Copy the kernel data segment descriptor into AX
	  mov   ds, ax     ; and then to all segment registers
	  mov   es, ax
	  mov   fs, ax
	  mov   gs, ax
	
    cld                 ; Clear the direction flag
	  call isr_handler    ; Call the C ISR handling function
	
	  pop   eax           ; Restore the general purpose registers
	  mov   ds, ax
	  mov   es, ax
	  mov   fs, ax
	  mov   gs, ax        ; Restore the segment registers
	  popa
	  add   esp, 8        ; Clean up the pushed error code and pushed ISR number
	  sti                 ; Set interrupt flag
	  iret                ; Interrupt return, pops CS, EIP, EFLAGS, SS, and ESP


;  Common IRQ function.
  irq_common:
    pusha               ; Pushes general purpose registers
	  mov   ax, ds        ; Move DS into the lower 16-bits of EAX
	  push  eax           ; Save the data segment descriptor
	  mov   ax, 0x10      ; Copy the kernel data segment descriptor into AX
	  mov   ds, ax        ; and then to all segment registers
	  mov   es, ax
	  mov   fs, ax
	  mov   gs, ax

    cld                 ; Clear the direction flag
    call  irq_handler   ; Call the C ISQ handling function

    pop   ebx           ; Restore the general purpose registers
    mov   ds, bx
    mov   es, bx
    mov   fs, bx
    mov   gs, bx        ; Set the segment registers to EBX
    popa
    add   esp, 8        ; Clean up the pushed error code and pushed ISR number
    sti                 ; Set interrupt flag
    iret                ; Interrupt return, pops CS, EIP, EFLAGS, SS, and ESP

; Define the C handling functions for the interrupt services registers and the
; interrupt requests.
[extern isr_handler]
[extern irq_handler]

; Define all of the interrupt routines.
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

; Define all of the interrupt requests.
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; ISR handlers.
isr0: ; Divide-by-zero exception
    cli
    push  byte 0
    push  byte 0
    jmp   isr_common


isr1: ; Debug exception
    cli
    push  byte 0
    push  byte 1
    jmp   isr_common


isr2: ; Non-maskable interrupt exception
    cli
    push  byte 0
    push  byte 2
    jmp   isr_common


isr3: ; Int 3 exception
    cli
    push  byte 0
    push  byte 3
    jmp   isr_common


isr4: ; INTO exception
    cli
    push  byte 0
    push  byte 4
    jmp   isr_common


isr5: ; Out-of-bounds exception
    cli
    push  byte 0
    push  byte 5
    jmp   isr_common


isr6: ; Invalid opcode exception
    cli
    push  byte 0
    push  byte 6
    jmp   isr_common


isr7: ; Co-processor not available exception
    cli
    push  byte 0
    push  byte 7
    jmp   isr_common


isr8: ; Double fault exception /w error code
    cli
    push byte 8
    jmp isr_common


isr9: ; Co-processor segment overrun exception
    cli
    push  byte 0
    push  byte 9
    jmp   isr_common


isr10: ; Bad TSS exception \w error code
    cli
    push byte 10
    jmp isr_common


isr11: ; Segment not present exception \w error code
    cli
    push byte 11
    jmp isr_common


isr12: ; Stack fault exception \w error code
    cli
    push byte 12
    jmp isr_common


isr13: ; General protection fault exception \w error code
    cli
    push byte 13
    jmp isr_common


isr14: ; Page fault exception
    cli
    push byte 14
    jmp isr_common


isr15: ; Reserved exception
    cli
    push  byte 0
    push  byte 15
    jmp   isr_common


isr16: ; Floating point exception
    cli
    push  byte 0
    push  byte 16
    jmp   isr_common


isr17: ; Aligment check exception
    cli
    push  byte 0
    push  byte 17
    jmp   isr_common


isr18: ; Machine check exception
    cli
    push  byte 0
    push  byte 18
    jmp   isr_common


isr19: ; Reserved
    cli
    push  byte 0
    push  byte 19
    jmp   isr_common


isr20: ; Reserved
    cli
    push  byte 0
    push  byte 20
    jmp   isr_common


isr21: ; Reserved
    cli
    push  byte 0
    push  byte 21
    jmp   isr_common


isr22: ; Reserved
    cli
    push  byte 0
    push  byte 22
    jmp   isr_common


isr23: ; Reserved
    cli
    push  byte 0
    push  byte 23
    jmp   isr_common


isr24: ; Reserved
    cli
    push  byte 0
    push  byte 24
    jmp   isr_common


isr25: ; Reserved
    cli
    push  byte 0
    push  byte 25
    jmp   isr_common


isr26: ; Reserved
    cli
    push  byte 0
    push  byte 26
    jmp   isr_common


isr27: ; Reserved
    cli
    push  byte 0
    push  byte 27
    jmp   isr_common


isr28: ; Reserved
    cli
    push  byte 0
    push  byte 28
    jmp   isr_common


isr29: ; Reserved
    cli
    push  byte 0
    push  byte 29
    jmp   isr_common


isr30: ; Reserved
    cli
    push  byte 0
    push  byte 30
    jmp   isr_common


isr31: ; Reserved
    cli
    push  byte 0
    push  byte 31
    jmp   isr_common


; IRQ handlers.
irq0:
	cli
	push  byte 0
	push  byte 32
	jmp   irq_common

irq1:
	cli
	push  byte 1
	push  byte 33
	jmp   irq_common

irq2:
	cli
	push  byte 2
	push  byte 34
	jmp   irq_common

irq3:
	cli
	push  byte 3
	push  byte 35
	jmp   irq_common

irq4:
	cli
	push  byte 4
	push  byte 36
	jmp   irq_common

irq5:
	cli
	push  byte 5
	push  byte 37
	jmp   irq_common

irq6:
	cli
	push  byte 6
	push  byte 38
	jmp   irq_common

irq7:
	cli
	push  byte 7
	push  byte 39
	jmp   irq_common

irq8:
	cli
	push  byte 8
	push  byte 40
	jmp   irq_common

irq9:
	cli
	push  byte 9
	push  byte 41
	jmp   irq_common

irq10:
	cli
	push  byte 10
	push  byte 42
	jmp   irq_common

irq11:
	cli
	push  byte 11
	push  byte 43
	jmp   irq_common

irq12:
	cli
	push  byte 12
	push  byte 44
	jmp   irq_common

irq13:
	cli
	push  byte 13
	push  byte 45
	jmp   irq_common

irq14:
	cli
	push  byte 14
	push  byte 46
	jmp   irq_common

irq15:
	cli
	push  byte 15
	push  byte 47
	jmp   irq_common