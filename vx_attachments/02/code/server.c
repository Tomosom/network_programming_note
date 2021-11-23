#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int server = 0;
    struct sockaddr_in saddr = {0};
    int client = 0;
    struct sockaddr_in caddr = {0};
    socklen_t asize = 0;
    int len = 0;
    char buf[32] = {0};
    int r = 0;

    server = socket(PF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        printf("server socket error\n");
        return -1;
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); /* htonl:将本机字节序转化为网络字节序 */
    saddr.sin_port = htons(8888);

    if (bind(server, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        printf("server bind error\n");
        return -1;
    }

    if (listen(server, 1) == -1) { /* 1:监听大小设置为1，表示每次只服务一个客户端 */
        printf("server listen error\n");
        return -1;
    }

    printf("server start success\n");

    while (1) {
        asize = sizeof(caddr);

        client = accept(server, (struct sockaddr*)&caddr, &asize);
        if (client == -1) {
            printf("client accept error\n");
            return -1;
        }

        printf("client: %d\n", client);

        do {
            //memset(buf, 0, sizeof(buf)); /* add */
            r = recv(client, buf, sizeof(buf), 0);
            if (r > 0) {
                printf("Receive: %s\n", buf);

                if (strcmp(buf, "quit") != 0) {
                    len = send(client, buf, r, 0);
                } else {
                    break;
                }
            }
        } while (r > 0);

        close(client);
    }

    close(server);
    return 0;
}
