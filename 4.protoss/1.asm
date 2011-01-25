org 07c00h
_1:
	mov ax,0h
	mov ds,ax
	mov es,ax

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
	lgdt [GDTpointer]
	lidt [IDTpointer]
	mov eax,cr0
	or eax,1h
	mov cr0,eax
	jmp 8:label0
label0:
	sti
	jmp 16:1234h
	cli
	hlt
GDTpointer:
	dw GDTlen - 1
	dd GDT
IDTpointer:
	dw 8*256
	dd IDT
int13:
	push ax
	push es
	mov ax,10h
	mov es,ax
	mov [es:0],word 'Hx'
	mov [es:2],word 'ex'
	mov [es:4],word 'lx'
	mov [es:6],word 'lx'
	mov [es:8],word 'ox'
	pop es
	pop ax
	cli
	hlt
GDT:
	db 8 dup(0)
	db 0xff,0xff,0x00,0x00,0x00,10011000b,00001111b,0x00
	db 0xff,0xff,0x00,0x80,0x0b,10010010b,00001111b,0x00
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
	repeat 242
	       dd 2 dup(0)
	end repeat