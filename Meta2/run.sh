lex mpascanner.l
yacc -d mpascanner.y
cc -o mpascanner y.tab.c lex.yy.c -ll -ly

./mpascanner < input.mpa > output.txt