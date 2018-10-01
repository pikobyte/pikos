;
; pikos_print32.asm
; Uses VGA instead of BIOS to print a string of text.
;

; Use 32-bit protected mode.
[bits 32]


; Define video constants.
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f


; Start by setting EDX to start of VGA memory.
print_string_pm:
    pusha
    mov   edx, VIDEO_MEMORY


; Loop over the string, printing the current character and end at the null
; termination character.
print_string_pm_loop:
    mov   al, [ebx]             ; Store the character in AL
    mov   ah, WHITE_ON_BLACK    ; Store the attributes in AH

    cmp   al, 0
    je    print_string_pm_done  ; Check null termination

    mov   [edx], ax             ; Store char and attribs
    inc   ebx                   ; Move to next char
    add   edx, 2                ; Move to next VGA cell

    jmp   print_string_pm_loop


; Restore stack state when returning.
print_string_pm_done:
    popa
    ret