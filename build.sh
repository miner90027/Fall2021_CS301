g++ -c main.cpp
nasm -f elf64 player.asm
g++ -no-pie -o run main.o player.o
