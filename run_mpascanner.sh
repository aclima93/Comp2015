clear

lex mpascanner.l
cc -o mpascanner lex.yy.c -ll

for i in {0..6}
	do
		./mpascanner < inputs_outputs/"$i"_input.mpa > inputs_outputs/"$i"_output.txt
done

zip mpascanner mpascanner.l