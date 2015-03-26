%{

#include<stdio.h>
%}

%token ASSIGN
%token BEGIN
%token DO
%token ELSE
%token END
%token FORWARD
%token FUNCTION
%token IF
%token OUTPUT
%token PARAMSTR
%token PROGRAM
%token RBRAC
%token REPEAT
%token THEN
%token UNTIL
%token VAL
%token VAR
%token WHILE
%token WRITELN
%token RESERVED
%token ID
%token REALLIT
%token INTLIT



%token OP2

%token OR
%token OP3
%left '!'
%left '|'

%left '&'
%token AND
%token OP4

%token NOT
%left '~'


%% 

Prog:  ProgHeading ';' ProgBlock '.';

ProgHeading: PROGRAM ID '(' OUTPUT ')';

ProgBlock: BEGIN END;


%%
int main(){
	yyparse();
}
