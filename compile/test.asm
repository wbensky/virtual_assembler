    .data
table:  .int 1,2, -1 ,4
utable: .uint 1,2, 5, 4
    .end_data
    .usect
        .int x,10
        .uint y, 10
    .end_usect
    .text
        irmovl rcx,4
loop:   irmovl rax, table
        nop
        irmovl rbx, x
        mrmovl rdx,rax
        rmmovl rdx,rbx
        cmpl rcx,0
        jg loop
    .end
