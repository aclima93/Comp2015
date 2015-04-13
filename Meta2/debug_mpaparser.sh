clear

lex mpaparser.l
yacc -d mpaparser.y -v
cc -o mpaparser y.tab.c lex.yy.c custom_structures.c -ll -ly -g

gdb mpaparser
