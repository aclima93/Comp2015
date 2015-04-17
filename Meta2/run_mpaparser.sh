clear

lex mpaparser.l
yacc -d mpaparser.y -v
cc -o mpaparser *.c -ll -ly

for i in {0..8}
	do
		./mpaparser -t -s < inputs_outputs_meta1/"$i"_input.mpa > inputs_outputs_meta1/"$i"_output.txt
done

for i in {0..11}
	do
		./mpaparser -t -s < inputs_outputs_meta2/"$i"_input.mpa > inputs_outputs_meta2/"$i"_output.txt
done

rm mpaparser.zip

zip mpaparser mpaparser.l mpaparser.y custom_structures.h custom_structures.c