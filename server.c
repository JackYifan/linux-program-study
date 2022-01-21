#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 8000
int main(){
    struct sockaddr_in servaddr,cliaddr;
    socklen_t cliaddr_len;
    int listenfd,connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    
    listenfd = socket(AF_INET,SOCK_STREAM,0); //listen connect request
    // constrcut servaddr
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    //Give the socket FD the local address ADDR (which is LEN bytes long).
    bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(listenfd,20);
    printf("Accepting connections\n");
    while (1)
    {
        cliaddr_len = sizeof(cliaddr);
        connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddr_len);
        int n = read(connfd,buf,MAXLINE);
        for(int i=0;i<n;i++){
            buf[i] = toupper(buf[i]);
        }
        write(connfd,buf,n);
        close(connfd);
    }
    

    
}