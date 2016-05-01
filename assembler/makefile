all: prog

prog: assembler.o parser.o
	g++ -Wall -pedantic -o assembler obj/assembler.o obj/parser.o
	
assembler.o: assembler.cpp
	g++ -Wall -pedantic -c assembler.cpp -o obj/assembler.o
	
parser.o: parser.cpp
	g++ -Wall -pedantic -c parser.cpp -o obj/parser.o
	
clean:
	rm obj/*o assembler.exe