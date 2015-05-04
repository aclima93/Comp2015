clear

lex mpasemantic.l
yacc -d mpasemantic.y -v
cc -o mpasemantic *.c -ll -ly

for i in {0..32}
	do
		./mpasemantic -s < inputs_outputs_meta3/"$i"_input.mpa > inputs_outputs_meta3/"$i"_output.txt
done

rm mpasemantic.zip

zip mpasemantic mpasemantic.l mpasemantic.y ASTree.h ASTree.c STable.c STable.h