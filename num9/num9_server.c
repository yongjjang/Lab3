#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MYPORT 12131 // 서버 포트
#define BACKLOG 10
#define MAXBUF 100

int main(int argc, char *argv[])
{
    int csock, ssock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    char buf[MAXBUF];
    int sin_size;

    if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(MYPORT);

    if (bind(ssock, (struct socketaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    // 연결 요구 허락
    if (listen(ssock, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    while (1)
    { // 클라이언트 요구 처리

        // 클라이언트 소켓 정보 획득
        sin_size = sizeof(struct sockaddr_in);
        if ((csock = accept(ssock, (struct sockaddr *)&clnt_addr, &sin_size)) == -1)
        {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n", inet_ntoa(clnt_addr.sin_addr));

        memset(buf, 0, MAXBUF);

        if (recv(csock, buf, MAXBUF, 0) == -1)
        {
            perror("recv");
            exit(0);
        }
        if (send(csock, buf, strlen(buf), 0) == -1)
        {
            perror("send");
            close(csock);
            exit(0);
        }
        close(csock);
    }
}