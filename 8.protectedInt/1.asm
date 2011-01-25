org 07c00h
_1:
	xor ax,ax
	mov ds,ax
	mov es,ax

	mov ax,0204h
	mov cx,0002h
	xor dx,dx
	mov bx,IDT
	int 13h
	jnc _not_error

_error:
	mov bp,buffer1
	mov ax,1301h
	mov bx,37h
	mov cx,0bh
	int 10h
	cli
	hlt
	buffer1 db "fatal error",0h
_not_error:
	cli
	mov al,00010011b
	out 20h,al
	mov al,00010000b
	out 21h,al
	mov al,00000001b
	out 21h,al
	mov al,11111101b
	out 21h,al
	lgdt [GDTpointer]
	lidt [IDTpointer]
	mov eax,cr0
	or eax,1h
	mov cr0,eax
	jmp 8:label0
label0:
	sti
label1:	
	hlt
	jmp label1
GDTpointer:
	dw GDTlen - 1
	dd GDT
IDTpointer:
	dw 8*256
	dd IDT
int13:
	call print_hello
	cli
	hlt
int17:
	push	ax
	in	al, 60h
	;in     al, 61h
	;or     al, 10000000b
	;out    61h, al
	;and    al, 01111111b
	;out    61h, al
	mov	al, 20h
	out	20h, al
	pop	ax

	call print_hello
	iret
hello dw "Hx","ex","lx","lx","oX"
pos dw 0
print_hello:
	push ax
	push es
	push bx
	push cx
	mov bx,hello
	mov cx,5h
	mov ax,10h
	mov es,ax
	mov si,[cs:pos]
print_hello_loop:
	mov ax,[cs:bx]
	mov [es:si],ax
	add bx,2
	add [pos],2
	add si,2
	loop print_hello_loop
	pop cx
	pop bx
	pop es
	pop ax
	ret
GDT:
	db 8 dup(0)
	db 0xff,0xff,0x00,0x00,0x00,10011000b,00001111b,0x00
	db 0x10,0x00,0x00,0x80,0x0b,10010010b,00000000b,0x00
GDTlen = $ - GDT

_end1:
	db 510 - (_end1 - _1) dup(0)
db 55h,0aah
IDT:
	repeat 13
		dd 2 dup(0)
	end repeat
	
	dw	int13,8h
	db	0h,10000111b
	dw	0h

	repeat 3
	       dd 2 dup(0)
	end repeat

	dw	int17,8h
	db	0h,10000111b
	dw	0h

	repeat 238
	       dd 2 dup(0)
	end repeat