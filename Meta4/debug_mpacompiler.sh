clear

lex mpacompiler.l
yacc -d mpacompiler.y -v
cc -o mpacompiler *.c -ll -ly -g

gdb mpacompiler
