clear

lex mpacompiler.l
yacc -d mpacompiler.y -v
cc -o mpacompiler *.c -ll -ly

rm mpacompiler.zip

zip mpacompiler mpacompiler.l mpacompiler.y ASTree.h ASTree.c STable.c STable.h LLVMCode.c LLVMCode.h