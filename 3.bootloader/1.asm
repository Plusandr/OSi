org 7c00h
_1:
	cli
	xor ax,ax
	mov ss,ax
	mov sp,ax
	sti

	mov ax,0x7c00
	mov es,ax
	mov ax,0201h
	mov cx,0002h
	xor dx,dx
	mov bx,0x1230
	int 13h
	jc _error
	mov bp,0x1230
	jmp _not_error
_error:
	mov bp,buffer1
_not_error:
	mov ax,1301h
	mov bx,37h
	mov cx,0bh
	int 10h
	cli
	hlt
	buffer1 db "fatal error",0h
_2:
	db 446 - (_2 -_1) dup(0)
_partition_table:
	db 64 dup(0)
_mbr_signature: 
	db 55h, 0aah
sector2 db "2-nd sector",0h
_3:
      db 512 -(_3 - sector2)  dup(0)