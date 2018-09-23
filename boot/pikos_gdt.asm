;
; pikos_gdt.asm
; pikOS global descriptor table functions.
;

; Create the null-descriptor.
gdt_start:
    dd 0x0
    dd 0x0


; Define the code segment descriptor.
gdt_code:
    dw 0xffff       ; Maximum size
    dw 0x0          ; Start at address 0
    db 0x0
    db 10011010b    ; Present, ring0, code
    db 11001111b    ; Largely default
    db 0x0


; Define the data segment description.
gdt_data:
    dw 0xffff       ; Maximum size
    dw 0x0          ; Start at address 0
    db 0x0
    db 10010010b    ; Present, ring0, data
    db 11001111b    ; Largely default
    db 0x0


; End label to find GDT size.
gdt_end:


; Define the GDT descriptor.
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size
    dd gdt_start                ; Start address


; Constants for the GDT segment descriptor offsets.
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start