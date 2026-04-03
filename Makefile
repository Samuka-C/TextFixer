EXE := .exe # swap to `EXE := ` for linux
cc := gcc # swap for your prefered c compiler

textFixer$(EXE): main.o mylib.a
	$(cc) main.o mylib.a -o textFixer$(EXE)

main.o: src/main.c src/debug/debug.h
	$(cc) -c src/main.c -o main.o

libs := debug.o string_basic.o text_file.o string_list.o string_op.o

mylib.a: $(libs) src/debug/debug.h
	ar rcs mylib.a $(libs)

debug.o: src/debug/debug.c src/debug/debug.h
	$(cc) -c src/debug/debug.c -o debug.o

string_basic.o: src/string\ basic/string_basic.c src/debug/debug.h
	$(cc) -c "src/string basic/string_basic.c" -o string_basic.o

text_file.o: src/string\ basic/text_file.c src/debug/debug.h
	$(cc) -c "src/string basic/text_file.c" -o text_file.o

string_list.o: src/string\ list/string_list.c src/debug/debug.h
	$(cc) -c "src/string list/string_list.c" -o string_list.o

string_op.o: src/string\ process/string_op.c src/debug/debug.h
	$(cc) -c "src/string process/string_op.c" -o string_op.o
