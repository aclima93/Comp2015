clear

lex mpascanner.l
yacc -d mpascanner.y
cc -o mpascanner lex.yy.c -ll

for i in {0..4}
	do
		./mpascanner < inputs_outputs/"$i"_input.mpa > inputs_outputs/"$i"_output.txt
done

rm mpascanner.zip

zip mpascanner mpascanner.l