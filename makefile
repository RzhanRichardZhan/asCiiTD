all: ctcp.c stcp.c
	gcc -o client ctcp.c
	gcc -o server stcp.c
