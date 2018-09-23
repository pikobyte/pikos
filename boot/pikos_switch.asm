;
; pikos_switch.asm
; Defines the functions to switch to and initialise 32-bit protected mode.
;

; Define the switch.
[bits 16]
switch_to_pm:
    cli                     ; Turn off interrupts
    lgdt [gdt_descriptor]   ; Load the GDT descriptor
    mov eax, cr0             
    or eax, 0x1             ; Set the control register to 1 indirectly
    mov cr0, eax
    jmp CODE_SEG:init_pm    ; Clear the pipeline with
                            ; a far jump


; 32-bit protected mode initialisation.
[bits 32]
init_pm:
    mov ax, DATA_SEG    ; Old segments are meaningless
    mov ds, ax          ; in this mode, so just point
    mov ss, ax          ; them to the data selector
    mov es, ax          ; defined in the GDT.
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000    ; Update stack position
    mov esp, ebp

    call BEGIN_PM       ; Start the mode