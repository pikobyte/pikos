;
; pikos_entry.asm
; Simply defines the calling point of main in the kernel.
;

[bits 32]
[extern main]
call main
jmp $