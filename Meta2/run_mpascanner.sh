clear

lex mpascanner.l
yacc -d mpascanner.y
cc -o mpascanner y.tab.c lex.yy.c -ll -ly

for i in {0..4}
	do
		./mpascanner < inputs_outputs/"$i"_input.mpa > inputs_outputs/"$i"_output.txt
done

rm mpascanner.zip

zip mpascanner mpascanner.l