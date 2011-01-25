format coff
public print as "_print"
print:
;euclid's algorithm
;
	push ebp
	mov ebp,esp
	mov eax,[ebp+4+4]
	mov ebx,[ebp+4+4+4]
	and eax,0xff
	and ebx,0xff
	cmp bl,0
	je _result
_algo:
	div bl
	mov al,ah
	mov ah,0
_swap:
	mov cl,al
	mov al,bl
	mov bl,cl
	cmp bl,0
	jne _algo
_result:
	pop ebp
	ret