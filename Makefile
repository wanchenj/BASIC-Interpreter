all: BI

ArithmeticExpression.o: ArithmeticExpression.h ArithmeticExpression.cpp
	g++ -g -Wall -c ArithmeticExpression.cpp -std=c++11 -o ArithmeticExpression.o

BooleanExpression.o: ArithmeticExpression.o BooleanExpression.h BooleanExpression.cpp
	g++ -g -Wall -c BooleanExpression.cpp -std=c++11 -o BooleanExpression.o

Command.o: Command.h Command.cpp
	g++ -g -Wall -c Command.cpp -std=c++11 -o Command.o

Interpreter.o: Interpreter.h Interpreter.cpp
	g++ -g -Wall -c Interpreter.cpp -std=c++11 -o Interpreter.o

Basic_Intepreter: Basic_Intepreter.cpp ArithmeticExpression.o BooleanExpression.o Command.o Interpreter.o
	g++ -g -Wall Basic_Intepreter.cpp ArithmeticExpression.o BooleanExpression.o Command.o Interpreter.o -std=c++11 -o Basic_Intepreter

.PHONY: clean

clean:
	rm BI
	rm -rf *.o
