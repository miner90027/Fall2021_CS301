section .text
	global player

; possible actions
; 	0 = no action (exit)
; 	1 = access health
; 	2 = access inventory
	player:
		
		cmp rdi, 1
		jne next
		mov rax, [playerPtr]
		jmp end
		
		next:
		cmp rdi, 2
		jne end
		mov rax, [inventoryPtr]
		jmp end
		
		end:
			ret
			
section .data
playerPtr:
	dd 100							; offset 0 Health
	;dd [inventoryPtr]	; offset 8 inventoryPtr

inventoryPtr:
	dq 0,0,0,0,0
