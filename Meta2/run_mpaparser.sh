clear

lex mpaparser.l
yacc -d mpaparser.y -v
cc -o mpaparser y.tab.c lex.yy.c custom_structures.c -ll -ly

for i in {0..4}
	do
		./mpaparser < inputs_outputs/"$i"_input.mpa > inputs_outputs/"$i"_output.txt
done

rm mpaparser.zip

zip mpaparser mpaparser.l mpaparser.y custom_structures.h custom_structures.c