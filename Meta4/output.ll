declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*) nounwind readonly


@str.int_lit = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@str.real_lit = private unnamed_addr constant [8 x i8] c"%f.12E\0A\00"
@str.false = private unnamed_addr constant [7 x i8] c"FALSE\0A\00"
@str.true = private unnamed_addr constant [6 x i8] c"TRUE\0A\00"
@str.bools = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8]* @str.true, i32 0, i32 0)]


