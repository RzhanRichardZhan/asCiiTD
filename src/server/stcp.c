#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>
char * process(char * s);
int id;
static void sighandler(int signo){
  ////////////////////////////////
  //Kills everything if canceled//
  ////////////////////////////////
  if (signo == SIGINT){
    if (getpid() != id){
      kill(getpid(),SIGINT);
    }
    exit(-1);
  }
}
int main(){
  id = getpid();
  signal(SIGINT,sighandler);
  int socket_id, socket_client;
  char buffer[256];
  int i,b;
  ////////////////////////
  //1. Create the socket//
  ////////////////////////
  socket_id = socket(AF_INET,SOCK_STREAM,0);//creates an IPv4 TCP
  ////////////////////////////
  //2. Bind socket to a port//
  ////////////////////////////
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port = htons(8000); //select a port (htons puts it in little Endian)
  listener.sin_addr.s_addr = INADDR_ANY; //select can use
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  ////////////////////////
  //3. Listen connection//
  ////////////////////////
  listen(socket_id,1); //listens
  printf("Listened\n");
  while(1){
    socket_client = accept(socket_id,NULL,NULL); //creates a new socket to handle this client
    printf("Accepted\n");
    ////////////////////////
    //4. Send/Receive data//
    ////////////////////////
    
    if (fork() == 0){
      close(socket_id);
      while(1){
	char input[1024]="";
	read(socket_client,input,1024);
	if (strcmp(input,"exit")==0){
	  break;
	}
	
	printf("Read: %s\n",input);
      }
      
      close(socket_client);
      printf("Client died\n");
      exit(-1);
    }
  }    
  
  //write(socket_client,"hello",6);
  return 0;
}
