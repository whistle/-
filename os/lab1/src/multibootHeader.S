.text
.globl  start, _start
start:
_start:
        movl $0x2f652f68, 0xB8000   //he
        movl $0x2f6c2f6c, 0xB8004   //ll
        movl $0x2f772f6f, 0xB8008   //ow
        movl $0x2f722f6f, 0xB800c   //or
        movl $0x2f642f6c, 0xB8010   //ld
        movl $0x2f502f2c, 0xB8014   //,P
        movl $0x2f312f42, 0xB8018   //B1
        movl $0x2f302f38, 0xB801c   //80
        movl $0x2f312f38, 0xB8020  //81
        movl $0x2f312f36, 0xB8024   //61
        movl $0x2f202f36, 0xB8028   //6
        movl $0x2f612f74, 0xB802c   //ta
        movl $0x2f792f6e, 0xB8030   //ny
        movl $0x2f612f75, 0xB8034   //ua
        movl $0x2f6e, 0xB8038 //n       
        .align  4
multiboot_header:         //multiboot协议
        .long   0x1BADB002
        .long   0x00000001
        .long   -(0x1BADB002 + 0x00000001)
loop:   hlt         //循环防止运行结果闪烁
    jmp loop
     