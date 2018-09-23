;
; pikos_print_hex.asm
; Allows the printing of a hexidecimal value. The data are received into the DX
; register.
;

; Push the current registers to the stack and set a counter variable in the CX
; register.
print_hex:
    pusha
    mov cx, 0

; Loop over the input four times the length of the hex input representation.
start_hex:
    cmp cx, 4
    je end_hex          ; End after 4 iterations

    mov ax, dx
    and ax, 0x000f      ; Masks first 3 values to zero
    add al, 0x30        ; Add to start at ASCII 0

    cmp al, 0x39        ; Check numeric range
    jle append_hex      ; Append character

    add al, 7           ; Add to start at ASCII A


; Puts the correspinding ASCII character into the defined output.
append_hex:
    mov bx, HEX_OUTPUT + 5
    sub bx, cx                  ; Move to current position

    mov [bx], al                ; Copy ASCII value
    ror dx, 4                   ; Rotate, shift all bits right

    inc cx
    jmp start_hex               ; Increment and reiterate


; Print out the converted hex value.
end_hex:
    mov bx, HEX_OUTPUT
    call print_str

    popa
    ret

; Declare memory for output string.
HEX_OUTPUT:
    db '0x0000', 0