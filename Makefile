.PHONY: pch

INCLUDE = "-ISFML-TGUI/include -Isrc/"
SOURCE = $(wildcard Core/*.cpp)
# PATH = $(shell pwd)

build:
	g++ -c $(SOURCE) $(INCLUDE)
	ar rcs Core.a $(wildcard *.o)

clean:
	rm -rf *.o

pch:
	g++ src/Pch.hpp -ISFML-TGUI/include

