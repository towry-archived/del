
all: bin
	gcc -g src/main.c src/mv.c -o bin/del

.PHONY: bin 
bin:
	mkdir -p bin

.PHONY: clean install
clean:
	rm -rf *.out *.a *.o

install: all
	install bin/del /usr/local/bin/
