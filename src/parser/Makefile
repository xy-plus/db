all: parser.y parser.l
	bison parser.y -d -o parser.tab.cpp
	flex parser.l
	mv lex.yy.c lex.yy.cpp

clean:
	rm *.o lex.yy.cpp parser.tab.cpp parser.tab.hpp
