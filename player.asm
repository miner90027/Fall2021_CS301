section .text
	global getHealth
	global getInventory

	getHealth:
		
		mov rax, [playerPtr]
		jmp end
		
	getInventory:
		
		mov rax, [inventoryPtr + 8*rdi]
		jmp end
		
		end:
			ret
			
section .data
playerPtr:
	dd 100							; offset 0 Health

inventoryPtr:
	dq 0,0,0,0,0
