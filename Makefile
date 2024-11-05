FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: built run dump
	
built:
	g++ -I./include ./src/*.cpp ${FLAGS} -o main
run:
	./main
dump:
	dot ./file_dot/file_0.dot  -Tpng -o ./file_dot/file_0.png
	dot ./file_dot/file_1.dot  -Tpng -o ./file_dot/file_1.png
	dot ./file_dot/file_2.dot  -Tpng -o ./file_dot/file_2.png
	dot ./file_dot/file_3.dot  -Tpng -o ./file_dot/file_3.png
	dot ./file_dot/file_4.dot  -Tpng -o ./file_dot/file_4.png
	dot ./file_dot/file_5.dot  -Tpng -o ./file_dot/file_5.png
	dot ./file_dot/file_6.dot  -Tpng -o ./file_dot/file_6.png
	dot ./file_dot/file_7.dot  -Tpng -o ./file_dot/file_7.png
	dot ./file_dot/file_8.dot  -Tpng -o ./file_dot/file_8.png
	dot ./file_dot/file_9.dot  -Tpng -o ./file_dot/file_9.png
	dot ./file_dot/file_10.dot -Tpng -o ./file_dot/file_10.png
