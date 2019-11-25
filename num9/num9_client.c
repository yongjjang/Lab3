#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define PORT 12131
#define MAXDATASIZE 100

int main(int argc, char* argv[]){
    int csock, numbytes;
    char buf[MAXDATASIZE];
    struct sockaddr_in serv_addr;
    int len;

    if(argc != 3){
        fprintf(stderr,"Usage: %s <SERVER IP> <ECHO STRING>\n", argv[0]);
        exit(1);
    }

    if(csock = socket(AF_INET, SOCK_STREAM, 0) == -1) {
        perror("socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(PORT);

    if(connect(csock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1){
        perror("connect");
        exit (1);
    }
    memset(buf, 0, MAXDATASIZE);
    strcpy(buf, argv[2]);
    len = strlen(buf);

    if(send(csock, buf, len, 0) != len){
        fprintf(stderr, "send failed...\n");
        exit(1);
    }

    memset(buf, 0, MAXDATASIZE);
    if ((numbytes = recv(csock, buf, MAXDATASIZE, 0)) == -1){
        perror("recv");
        exit(1);
    }
    printf("Received: %s\n", buf);

    close(csock);
}