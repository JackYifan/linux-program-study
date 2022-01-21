#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc,char* argv[]){
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    char* str;
    str = argv[1];

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    // server addr
    bzero(&servaddr,sizeof servaddr);
    servaddr.sin_family = AF_INET; //ipv4 
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);// ip
    servaddr.sin_port = htons(SERV_PORT); //port
    //Open a connection on socket FD to peer at ADDR
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 
    write(sockfd,str,strlen(str));
    int n = read(sockfd,buf,MAXLINE);
    printf("Response From Server:\n");
    write(STDOUT_FILENO,buf,n);
    printf("\n");
    close(sockfd);
    return 0;
}