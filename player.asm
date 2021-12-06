section .text
	global getHealth
	global inventoryPtr
	global attack
	
	getHealth:
		mov rax, QWORD[playerPtr +8*0]
		ret
		
	enemyHealth:
		mov rax, QWORD[enemyPtr +8*0]
		ret
	
	attack:
		cmp rdi, 0
		jne .hitPlayer
		
		.hitEnemy:
			mov rcx, [playerPtr+8*1]
			sub [enemyPtr+8*0], rcx
			cmp QWORD[enemyPtr+8*0], 0
			jle .end
			jmp enemyHealth
		
		.hitPlayer:
			mov rcx, [enemyPtr+8*1]
			sub [playerPtr+8*0], rcx
			cmp QWORD[playerPtr+8*0], 0
			jle .end
			jmp getHealth
			
			.end:
				xor rax, rax
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

