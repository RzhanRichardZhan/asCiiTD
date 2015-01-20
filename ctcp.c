#include <sys/socket.h>
#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char **argv){
  int socket_id;
  char buffer[256];
  int i,b;
  ////////////////////////
  //1. Create the socket//
  ////////////////////////
  socket_id = socket(AF_INET,SOCK_STREAM,0);//creates an IPv4 TCP
  /////////////////////////////
  //2. Bind socket to address//
  /////////////////////////////
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(8000); //select a port
  inet_aton("127.0.0.1",&(sock.sin_addr)); //using localhost
  bind(socket_id,(struct sockaddr *)&sock,sizeof(sock));
  //////////////////////////
  //4. Initiate connection//
  //////////////////////////
  i = connect(socket_id,(struct sockaddr *)&sock,sizeof(sock)); //connect
  while(1){
    printf("%d>",i);
    char input[1024];
    fgets(input,sizeof(input),stdin);
    input[strlen(input)-1]=0;
    printf("<%s>\n",input);
    write(socket_id,input,strlen(input));
  }
  
  return 0;
}
