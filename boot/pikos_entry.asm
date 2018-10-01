;
; pikos_entry.asm
; Simply defines the calling point of main in the kernel.
;

global _start
[bits 32]

_start:
    [extern pikos_main]
    call  pikos_main
    jmp   $