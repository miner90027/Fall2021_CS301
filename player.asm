section .text
	global getHealth
	global getInventory
	global setInventory

	getHealth:
		mov rax, [playerPtr]
		;mov rax, rcx
		ret
		
	getInventory:
		mov rax, QWORD[inventoryPtr + 8*rdi]
		ret
		
	setInventory:
		mov [inventoryPtr + 8*rdi], rsi
		mov rax, 0
		ret
		
		
	
			
section .data
playerPtr:
	dq 100	; Health
	;dd 1      ; Attack

inventoryPtr:
	dq 0,0,0,0,0

	
enemyPtr:
	dd 50    ; Health
	dd 1     ; Attack
