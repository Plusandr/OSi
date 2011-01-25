org 7c00h
_1:
	cli
	xor ax,ax
	mov ss,ax
	mov sp,ax
	sti

	mov es,ax
	mov ax,0201h
	mov cx,0002h
	xor dx,dx
	mov bx,sector2
	int 13h
	jc _error
	mov bp,sector2
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
	db 510 - (_2 -_1) dup(0)
	db 55h, 0aah
sector2 db "2-nd sector",0h
_3:
      db 512 -(_2 - sector2)  dup(0)