/*
Author:        Miguel A. Martinez
ID:            10887477
Course:        CSCE 3530 - Introduction to Computer Networks
Professor:     Dr. Robin
Date:          9/28/2016
Filename:      "pserver.c"
Description:   A proxy server which accepts a connection from a client, recieves a web URL via socket,
                  then connects to the website server using port 80. A get request is sent and all 
                  data is then sent to the client (which saves it onto disk)
Note:          The resultant HTML file contains the header from the GET request, so opening 
                  the file in a web browser gives a weird look. The user may delete the 
                  header by opening the file up in a text editor.        */

#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define WEBPORT 80

void error(const char *msg)
{
   perror(msg);
   exit(1);
}

int socket_connect(char *host, in_port_t port){
   struct hostent *hp;
   struct sockaddr_in addr;
   int on = 1, sock;     
   if((hp = gethostbyname(host)) == NULL){
      herror("gethostbyname");
      exit(1);
   }
   bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
   addr.sin_port = htons(WEBPORT);
   addr.sin_family = AF_INET;
   sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
   if(sock == -1){
      perror("setsockopt");
      exit(1);
   }
   if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
      perror("connect");
      exit(1);
   }
   return sock;
}



int main(int argc, char *argv[])
{
   int sockfd, newsockfd, portno, pid;
   socklen_t clilen;
   struct sockaddr_in serv_addr, cli_addr;
   if (argc != 2) {
      fprintf(stderr,"format: %s [port#]\n", argv[0]);
      exit(1);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) 
      error("ERROR opening socket");
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = atoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
      error("ERROR on binding");
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   int n;
   char buffer1[256];
   
   newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
   if (newsockfd < 0) 
      error("ERROR on accept");
   bzero(buffer1,256);
   n = read(newsockfd,buffer1,255);
   if (n < 0) 
      error("ERROR reading from socket");
   buffer1[strlen(buffer1)-1] = '\0'; 
   char* test = strdup(buffer1);
   printf("host address: %s\n",test);
   n = write(newsockfd,"message received\n",18);
   if (n < 0) 
      error("ERROR writing to socket");
   int fd;
   
   char buffer[BUFFER_SIZE];           
   fd = socket_connect(test, 80); 
   write(fd, "GET /\r\n", strlen("GET /\r\n"));  
   bzero(buffer, BUFFER_SIZE);
   while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
      n = write(newsockfd,buffer, strlen(buffer));          
      bzero(buffer, BUFFER_SIZE);
   }

   shutdown(fd, SHUT_RDWR); 
   close(fd); 
   close(newsockfd);     
   printf("\nThe request is saved in 'assignment1.html' \n (please note it includes the GET request header)\n");
   return 0;
}