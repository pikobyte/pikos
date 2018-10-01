;
; pikos_bootsect.asm
;
; pikOS boot sector which switches to 32-bit protected mode and launches the
; kernel.

; Bootloader offset.
[org 0x7c00]
KERNEL_OFFSET equ 0x1000    ; Set a location to link the kernel
    mov   [BOOT_DRIVE], dl  ; Set boot drive.

    mov   bp, 0x9000
    mov   sp, bp            ; Set the stack

    mov   bx, MSG_REAL_MODE
    call  print_str         ; Print boot mode.
    call  print_ln

    call  load_kernel       ; Read the kernel.
    call  switch_to_pm      ; 32-bit mode.
    jmp   $


; Include necessary files for used functions.
%include "boot/pikos_print_str.asm"
%include "boot/pikos_print_hex.asm"
%include "boot/pikos_print32.asm"
%include "boot/pikos_disk.asm"
%include "boot/pikos_gdt.asm"
%include "boot/pikos_switch.asm"


; Load the kernel from the drive.
[bits 16]
load_kernel:
    mov   bx, MSG_LOAD_KERNEL
    call  print_str
    call  print_ln

    mov   bx, KERNEL_OFFSET  ; Read the kernel from the
    mov   dh, 16             ; disc and store at the
    mov   dl, [BOOT_DRIVE]   ; 16 sectors at 0x1000

    call  disk_load
    ret


; Hand over control to the kernel.
[bits 32]
BEGIN_PM:
    mov   ebx, MSG_PROT_MODE
    call  print_string_pm    ; Print 32-bit switch message

    call  KERNEL_OFFSET      ; Gives control to the kernel
    jmp   $


; Message declarations.
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0


; Declare memory for the boot drive.
BOOT_DRIVE db 0


; Create the boot-sector.
times 510-($-$$) db 0
dw    0xaa55