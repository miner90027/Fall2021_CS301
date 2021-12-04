section .text
	global getHealth
	global inventoryPtr

	getHealth:
		mov rax, QWORD[playerPtr +8*0]
		;mov rax, rcx
		ret
		
	
	
	
			
section .data
playerPtr:
	dq 100	; Health
	dq 1      ; Attack
	
enemyPtr:
	dq 50    ; Health
	dq 1     ; Attack

inventoryPtr:
	dq 0,0,0,0,0

