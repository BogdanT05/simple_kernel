.global trapHandler
.extern syscallHandler

trapHandler:
    csrr t0, sepc
    call syscallHandler

    addi t0, t0, 4
    csrw sepc, t0

    sret