clear

lex mpasemantic.l
yacc -d mpasemantic.y -v
cc -o mpasemantic y.tab.c lex.yy.c custom_structures.c -ll -ly -g

gdb mpasemantic
