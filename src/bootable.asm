[bits 16]
[org 0x7C00]

hlt

times 510 - ($ - $$) db 0x0
dw 0xAA55
