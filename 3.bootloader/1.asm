org 7c00h
_1:
	cli
	xor ax,ax
	mov ss,ax
	mov sp,ax
	sti
_2:
	mov es,ax
	mov ax,0201h
	mov cx,0002h
	xor dx,dx
	mov bx,buffer2
	int 13h
	jc _error
	mov bp,buffer2
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
	buffer2 db "1-st sector"
_3:
	db 510 - (_3 -_1) dup(0)
	db 55h, 0aah
sector2 db "2-nd sector",0h
_4:
      db 512 -(_4 - sector2)  dup(0)
