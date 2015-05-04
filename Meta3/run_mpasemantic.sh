clear

lex mpasemantic.l
yacc -d mpasemantic.y -v
cc -o mpasemantic *.c -ll -ly

for i in {0..42}
	do
		./mpasemantic -s < inputs_outputs_meta3/"$i"_input.mpa > inputs_outputs_meta3/"$i"_output.txt

		# diff it
		result=$(diff -y -W 72 expected_outputs/"$i"_output.txt inputs_outputs_meta3/"$i"_output.txt)

		if [ $? -ne 0 ]
		then
			echo ""
	        echo "file " $i " is different"
	        echo ""
	        diff -c expected_outputs/"$i"_output.txt inputs_outputs_meta3/"$i"_output.txt
	        echo ""
		fi

done

rm mpasemantic.zip

zip mpasemantic mpasemantic.l mpasemantic.y ASTree.h ASTree.c STable.c STable.h