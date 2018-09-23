;
; pikos_print_str.asm
; Contains simple function for printing strings and a new line. The data are
; received into the BX register.
;

; Push all of the current registers onto the stack.
print_str:
    pusha

; Loop over the string, printing the current character and end at the null
; termination character.
start_str:
    mov al, [bx]
    cmp al, 0 
    je end_str      ; Check null termination

    
    mov ah, 0x0e
    int 0x10        ; Print the current character

    add bx, 1
    jmp start_str   ; Reiterate


; Return, restoring stack state.
end_str:
    popa
    ret


; Print newline.
print_ln:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; Newline character
    int 0x10
    mov al, 0x0d ; Carriage return
    int 0x10
    
    popa
    ret