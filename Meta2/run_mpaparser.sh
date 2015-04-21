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

		# diff it
		result=$(diff -y -W 72 inputs_outputs_meta2/"$i"_output_expected.txt inputs_outputs_meta2/"$i"_output.txt)

		if [ $? -ne 0 ]
		then
			echo ""
	        echo "file " $i " is different"
	        echo ""
	        diff -c inputs_outputs_meta2/"$i"_output_expected.txt inputs_outputs_meta2/"$i"_output.txt
	        echo ""
		fi
done

rm mpaparser.zip

zip mpaparser mpaparser.l mpaparser.y custom_structures.h custom_structures.c