

declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*) nounwind readonly


@str.int_lit = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@str.real_lit = private unnamed_addr constant [8 x i8] c"%f.12E\0A\00"
@str.false = private unnamed_addr constant [7 x i8] c"FALSE\0A\00"
@str.true = private unnamed_addr constant [6 x i8] c"TRUE\0A\00"
@str.blank_line = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@str.bools = global [2 x i8*] [i8* getelementptr inbounds ([7 x i8]* @str.false, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8]* @str.true, i32 0, i32 0)]


define i32 @paramcount(){

	ret i32 0
}

define i32 @gcd(i32 %a.param, i32 %b.param){

	%a = alloca i32
	store i32 %a.param, i32* %a
	%b = alloca i32
	store i32 %b.param, i32* %b
		br i1 %1, label %if.then1, label %if.else1

		if.then1:
			store i32* %gcd, i32* %2
			br label %if.end1

		if.else1:
				br label %while.start2

				while.start2:
					br i1 %3, label %while.do2, label %while.end2

				while.do2:
					br i1 %4, label %if.then3, label %if.else3

					if.then3:
						store i32* %a, i32* %5
						br label %if.end3

					if.else3:
						store i32* %b, i32* %6
						br label %if.end3

					if.end3:
					br label %while.start2

				while.end2:
			br label %if.end1

		if.end1:
	ret i32 0
}

define void @main(i32 %argc, i8** %argv) #0 {

	%1 = alloca i32, align 4
	%2 = alloca i32, align 4
	%3 = alloca i8**, align 8
	store i32 0, i32* %1
	store i32 %argc, i32* %2, align 4
	store i8** %argv, i8*** %3, align 8

	%x = alloca i32
	%y = alloca i32

	ret void
}

