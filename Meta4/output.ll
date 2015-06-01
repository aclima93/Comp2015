declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*) nounwind readonly


@str.int_lit = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@str.real_lit = private unnamed_addr constant [8 x i8] c"%f.12E\0A\00"
@str.false = private unnamed_addr constant [7 x i8] c"FALSE\0A\00"
@str.true = private unnamed_addr constant [6 x i8] c"TRUE\0A\00"
@str.bools = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8]* @str.true, i32 0, i32 0)]


define i32 @gcd(i32 %A.param, i32 %B.param)
{
	br i1 %0, label %if.then2, label %if.else2

if.then2:
	br label %if.end2

if.else2:
	br label %while.start0

while.start0:
	br i1 %0, label %while.do0, label %while.end0

while.do0:
	br i1 %0, label %if.then3, label %if.else3

if.then3:
	br label %if.end3

if.else3:
	br label %if.end3

if.end3:
	br label %while.start0

while.end0:
	br label %if.end2

if.end2:
	ret i32 0
}

define void @main()
{
	%x = alloca i32
	%y = alloca i32

	br i1 %205338058, label %if.then4, label %if.else4

if.then4:
	br label %if.end4

if.else4:
	br label %if.end4

if.end4:
	ret void
}

