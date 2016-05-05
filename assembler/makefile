all: prog

prog: assembler.o parser.o code.o
	g++ -std=c++11 -Wall -pedantic -o assembler obj/assembler.o obj/parser.o obj/code.o
	
assembler.o: assembler.cpp
	g++ -std=c++11 -Wall -pedantic -c assembler.cpp -o obj/assembler.o
	
parser.o: parser.cpp
	g++ -std=c++11 -Wall -pedantic -c parser.cpp -o obj/parser.o
	
code.o: code.cpp
	g++ -std=c++11 -Wall -pedantic -c code.cpp -o obj/code.o
	
clean:
	rm obj/*o assembler.exe