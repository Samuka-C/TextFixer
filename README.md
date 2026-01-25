compile all library source code:
`gcc -c [file.c]`

bundle them into a library
`rm mylib.a`
`ar rcs mylib.a *.o`

update library with single new compiled source code
`gcc -c [file.c]`
`ar rcs mylib.a [file.o]`

compile the main source file
`gcc main.c mylib.a -o textFixer`