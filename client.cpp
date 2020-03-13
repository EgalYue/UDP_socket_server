#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define DEST_PORT 8000
#define DSET_IP_ADDRESS  "127.0.0.1"


#define bind_port_ 4567


int main()
{
    /* socket文件描述符 */
    int sock_fd;

    /* 建立udp socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
    {
        perror("socket");
        exit(1);
    }


    // bind socket
    sockaddr_in client_bind_addr;
    client_bind_addr.sin_family = AF_INET;
    client_bind_addr.sin_port = htons(bind_port_);
    client_bind_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock_fd, (sockaddr *)&client_bind_addr,
             sizeof(client_bind_addr)) != 0) {
        printf("bind port %d failed with error \n",
               bind_port_);
        close(sock_fd);
    }






    /* 设置address */
    sockaddr_in addr_serv;
    int len = sizeof(struct sockaddr);
//    memset(&addr_serv, 0, sizeof(addr_serv));
//    addr_serv.sin_family = AF_INET;
//    addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
//    addr_serv.sin_port = htons(DEST_PORT);
//    len = sizeof(addr_serv);


//    int send_num;
    int recv_num;
//    char send_buf[20] = "message from client";
    char recv_buf[20];
//
//    printf("client send: %s\n", send_buf);
//
//    send_num = sendto(sock_fd, send_buf, strlen(send_buf), 0, (struct sockaddr *)&addr_serv, len);
//
//    if(send_num < 0)
//    {
//        perror("sendto error:");
//        exit(1);
//    }

    recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, reinterpret_cast<sockaddr *>(&addr_serv), (socklen_t *)&len);
    printf("get message from: %s : %d\n", inet_ntoa(*((struct in_addr*)&addr_serv.sin_addr)), ntohs(addr_serv.sin_port));

    if(recv_num < 0)
    {
        perror("recvfrom error:");
        exit(1);
    }

    recv_buf[recv_num] = '\0';
    printf("client receive %d bytes: %s\n", recv_num, recv_buf);

    close(sock_fd);

    return 0;
}