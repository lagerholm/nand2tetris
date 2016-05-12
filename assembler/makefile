.all: assembler

assembler: obj/assembler.o obj/parser.o obj/code.o obj/symbolTable.o
	g++ -std=c++11 -Wall -pedantic -o assembler obj/assembler.o obj/parser.o obj/code.o obj/symbolTable.o
	
obj/assembler.o: assembler.cpp
	g++ -std=c++11 -Wall -pedantic -c assembler.cpp -o obj/assembler.o
	
obj/parser.o: parser.cpp
	g++ -std=c++11 -Wall -pedantic -c parser.cpp -o obj/parser.o
	
obj/code.o: code.cpp
	g++ -std=c++11 -Wall -pedantic -c code.cpp -o obj/code.o
	
obj/symbolTable.o: symbolTable.cpp
	g++ -std=c++11 -Wall -pedantic -c symbolTable.cpp -o obj/symbolTable.o
	
clean:
	rm obj/*o assembler.exe