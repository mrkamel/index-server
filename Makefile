
BIN = query_server
CC = gcc

project: tmp/main.o tmp/string.o tmp/array.o tmp/hash.o tmp/index.o tmp/and_combination.o tmp/query.o tmp/socket.o tmp/stdin.o tmp/request.o
	$(CC) -lpthread tmp/*.o -o bin/$(BIN)

tmp/request.o: src/request.c
	$(CC) -c src/request.c -o tmp/request.o

tmp/stdin.o: src/stdin.c
	$(CC) -c src/stdin.c -o tmp/stdin.o

tmp/socket.o: src/std/socket.c
	$(CC) -c src/std/socket.c -o tmp/socket.o

tmp/query.o: src/query.c
	$(CC) -c src/query.c -o tmp/query.o

tmp/and_combination.o: src/and_combination.c
	$(CC) -c src/and_combination.c -o tmp/and_combination.o

tmp/index.o: src/index.c
	$(CC) -c src/index.c -o tmp/index.o

tmp/main.o: src/main.c
	$(CC) -c src/main.c -o tmp/main.o

tmp/string.o: src/std/string.c
	$(CC) -c src/std/string.c -o tmp/string.o

tmp/array.o: src/std/array.c
	$(CC) -c src/std/array.c -o tmp/array.o

tmp/hash.o: src/std/hash.c
	$(CC) -c src/std/hash.c -o tmp/hash.o

clean: 
	rm -f tmp/*.o $(BIN)


