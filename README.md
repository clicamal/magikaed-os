# Magikaed OS

Um sistema operacional x86 simples. Criado seguindo o tutorial da https://wiki.osdev.org

## Emulando o sistema

Para emular o sistema você vai precisar destes programas:
 - i386 ELF GCC
 - i386 ELF AS
 - Qemu System i386
 - Make

Com esses programas instalados e acessíveis no PATH, execute:
```
make emulate
```

O comando acima compila, linka e inicia a emulação do kernel no Qemu.

Este comando apaga os arquivos gerados:
```
make clean
```
