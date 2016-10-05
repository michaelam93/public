/*
Author:        Miguel A. Martinez
ID:            10887477
Course:        CSCE 3530 - Introduction to Computer Networks
Professor:     Dr. Robin
Date:          9/28/2016
Filename:      "pclient.c"
Description:   A client interface that connects to a proxy server ran on cse01 (UNT server), 
                  accepts a cstring intended to be an ASCII url address, sends it to the 
                  proxy server and writes all recieved data to a file (which is an html file)
Note:          The resultant HTML file contains the header from the GET request, so opening 
                  the file in a web browser gives a weird look. The user may delete the 
                  header by opening the file up in a text editor.        */

#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVERADDR "cse01.cse.unt.edu"
#define BUFFER_SIZE 1024

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   FILE *fp = fopen ("assignment1.html", "w+");

   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   char buffer[256];
   if (argc != 2) {
      fprintf(stderr,"usage: %s [port#]\n", argv[0]);
      exit(1);
   }
   portno = atoi(argv[1]);
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) 
      error("ERROR opening socket");
   server = gethostbyname(SERVERADDR);
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, 
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);
   serv_addr.sin_port = htons(portno);
   if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      error("ERROR connecting");
   printf("url: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n = write(sockfd,buffer,strlen(buffer)+1);
   if (n < 0) 
      error("ERROR writing to socket");
   bzero(buffer,256);
   n = read(sockfd,buffer,255);
   if (n < 0) 
      error("ERROR reading from socket");
   printf("%s\n",buffer);
   char buffer2[BUFFER_SIZE];
   while(read(sockfd,buffer2,BUFFER_SIZE-1) != 0){
      fprintf(fp, "%s", buffer2);
   }
   printf("The request is saved in 'assignment1.html' \n (please note it includes the GET request header)\n");
   close(sockfd);
   return 0;
}