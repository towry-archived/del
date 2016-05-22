
all: bin
	g++ src/main.cc -o bin/del

.PHONY: bin 
bin:
	mkdir -p bin

.PHONY: clean
clean:
	rm -rf *.out *.a *.o
