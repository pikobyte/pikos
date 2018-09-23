;
; pikos_disk.asm
; pikOS disk handling routine.
;

; A typical disk is accessed through 3 values: cylinder, head and sector (CHS).
; We can use the BIOS interrupt int 0x13 after setting al to 0x02 to access a
; disk.

; Load the sectors in DH from the drive in DL into the register ES:BX.
disk_load:
    pusha               ; Push all of the registers onto the stack
    push dx             ; Store number of sectors to be read

    mov ah, 0x02
    mov al, dh          ; Read DH number of sectors

    mov cl, 0x02        ; Start reading from the sector after the boot sector
    mov ch, 0x00        ; Select cylinder 0
    mov dh, 0x00        ; Select head 0

    int 0x13            ; BIOS disk interrupt

    jc disk_error       ; Show error if overflow occurred
    pop dx
    cmp al, dh
    jne sectors_error   ; Show error if incorrect number of sectors read

    popa
    ret                 ; Restore stack state and return


; Prints the disk error, the disk which gave the error as well as the error 
; code. Hang the program if an error is given.
disk_error:
    mov bx, DISK_ERROR
    call print_str
    call print_ln
    mov dh, ah
    call print_hex
    jmp $


; Prints out the sectors error.
sectors_error:
    mov bx, SECTORS_ERROR
    call print_str


; Error string variables.
DISK_ERROR: db "Disk read error!", 0
SECTORS_ERROR: db "Incorrect number of sectors read!", 0