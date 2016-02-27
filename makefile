objects = Main.o Dictionary.o IO.o Search.o

CXX = g++ -std=c++0x

zoogle : $(objects)
	g++ -o  zoogle $(objects)

$(objects) : Dictionary.h

run : $(objects)
	g++ -o  zoogle $(objects)
	./zoogle
.PHONY : clean
clean:
	rm zoogle $(objects)
