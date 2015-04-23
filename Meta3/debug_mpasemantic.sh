clear

lex mpasemantic.l
yacc -d mpasemantic.y -v
cc -o mpasemantic *.c -ll -ly -g

gdb mpasemantic
