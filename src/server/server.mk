all: src/server/ctcp.c src/server/stcp.c
	gcc -o client src/server/ctcp.c
	gcc -o server src/server/stcp.c
