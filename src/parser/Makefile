all: parser.y parser.l
	bison parser.y
	flex parser.l
	mv lex.yy.c lex.yy.cpp
	mv parser.tab.c parser.tab.cpp
