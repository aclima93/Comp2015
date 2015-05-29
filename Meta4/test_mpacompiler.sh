clear

lex mpacompiler.l
yacc -d mpacompiler.y -v
cc -o mpacompiler *.c -ll -ly -g

./mpacompiler -s < input.mpa > output.ll
lli output.ll 12 8
