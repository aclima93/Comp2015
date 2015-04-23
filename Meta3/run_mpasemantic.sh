clear

lex mpasemantic.l
yacc -d mpasemantic.y -v
cc -o mpasemantic *.c -ll -ly

for i in {0..8}
	do
		./mpasemantic -s < inputs_outputs_meta1/"$i"_input.mpa > inputs_outputs_meta1/"$i"_output.txt
done

for i in {0..15}
	do
		./mpasemantic -s < inputs_outputs_meta2/"$i"_input.mpa > inputs_outputs_meta2/"$i"_output.txt

		# diff it
		result=$(diff -y -W 72 inputs_outputs_meta2/"$i"_output_expected.txt inputs_outputs_meta2/"$i"_output.txt)

		if [ $? -ne 0 ]
		then
			#say "god damn it"
			echo ""
	        echo "file " $i " is different"
	        echo ""
	        diff -c inputs_outputs_meta2/"$i"_output_expected.txt inputs_outputs_meta2/"$i"_output.txt
	        echo ""
		fi
done

for i in {0..15}
	do
		./mpasemantic -s < inputs_outputs_meta3/"$i"_input.mpa > inputs_outputs_meta3/"$i"_output.txt
done

rm mpasemantic.zip

zip mpasemantic mpasemantic.l mpasemantic.y custom_structures.h custom_structures.c