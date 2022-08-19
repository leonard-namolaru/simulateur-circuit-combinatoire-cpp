CPP=g++ --std=c++11

CFLAGS= -Wall

all : mr

mr : Gate.o Circuit.o CircuitException.o main.o Outils.o AndGate.o InputGate.o OrGate.o OutputGate.o XorGate.o NandGate.o NorGate.o XnorGate.o
	$(CPP) $(CFLAGS) -o $@ $^

Gate.o : Gate.cpp Gate.hpp
	$(CPP) $(CFLAGS) -c $<

Circuit.o : Circuit.cpp Circuit.hpp
	$(CPP) $(CFLAGS) -c $<

CircuitException.o : CircuitException.cpp CircuitException.hpp
	$(CPP) $(CFLAGS) -c $<

main.o : main.cpp 
	$(CPP) $(CFLAGS) -c $<

Outils.o : Outils.cpp Outils.hpp
	$(CPP) $(CFLAGS) -c $<

AndGate.o : AndGate.cpp AndGate.hpp
	$(CPP) $(CFLAGS) -c $<

InputGate.o : InputGate.cpp InputGate.hpp
	$(CPP) $(CFLAGS) -c $<

OrGate.o : OrGate.cpp OrGate.hpp
	$(CPP) $(CFLAGS) -c $<

OutputGate.o : OutputGate.cpp OutputGate.hpp
	$(CPP) $(CFLAGS) -c $<

XorGate.o : XorGate.cpp XorGate.hpp
	$(CPP) $(CFLAGS) -c $<

NandGate.o : NandGate.cpp NandGate.hpp
	$(CPP) $(CFLAGS) -c $<

NorGate.o : NorGate.cpp NorGate.hpp
	$(CPP) $(CFLAGS) -c $<

XnorGate.o : XnorGate.cpp XnorGate.hpp
	$(CPP) $(CFLAGS) -c $<	

clean :
	rm *.o
test:
	./mr

	