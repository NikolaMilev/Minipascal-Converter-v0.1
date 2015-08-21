PROGRAM = minipascal
CC = g++
CFLAGS = -Wall -pedantic -ansi
YACC = bison
LEX = flex
YFLAGS =  -d -v

$(PROGRAM) : parser.tab.o lex.yy.o expression.o statement.o
	$(CC) $(CFLAGS) -o $@ $^
parser.tab.o: parser.tab.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.h : parser.ypp
	$(YACC) $(YFLAGS) $<
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
lex.yy.c: lexer.l
	$(LEX) $<
expression.o: expression.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
statement.o: statement.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	-rm -f *.o *.c *~ minipascal parser.tab.* parser.output y.output
