#include <string.h>
#include <arpa/inet.h>

#include "./handle_common.h"
#include "./handle_socket.h"

void handle_socket_open(int *__socket_fd_out, struct sockaddr_in *__addr)
{
    int socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_fd == -1) { handle_error("handle_socket_open", "socket() failed to open."); return; }

    if(bind(socket_fd, (struct sockaddr *)&__addr, sizeof(__addr)) == -1)
    { handle_error("handle_socket_open", "bind() failed."); return; }

    *__socket_fd_out = socket_fd;
}

void handle_socket_close(int __socket_fd)
{
    close(__socket_fd);
}

void handle_socket_listen(int __socket_fd, int __wait_queue)
{
    if(listen(__socket_fd, __wait_queue) == -1)
    { handle_error("handle_socket_listen", "listen() failed."); return; }
}

void handle_socket_accept(int __socket_fd, struct sockaddr_in *__client_addr, int *__client_addr_len_out)
{
    if(accept(__socket_fd, (struct sockaddr *)&__client_addr, __client_addr_len_out) == -1)
    { handle_error("handle_socket_accept", "accept() failed."); return; }
}

void handle_socket_connect(int __socket_fd, struct sockaddr_in *__server_addr, int __server_addr_len)
{
    if(connect(__socket_fd, (struct sockaddr *)&__server_addr, __server_addr_len) == -1)
    { handle_error("handle_socket_connect", "connect() failed."); return; }
}

void handle_put_address(struct sockaddr_in *__out, char *__ip_address, int __port)
{
    __out->sin_family       = AF_INET;
    __out->sin_port         = htons(__port);
    __out->sin_addr.s_addr  = htonl(inet_addr(__ip_address));
}

void handle_get_address(char *__out, struct sockaddr_in *__ip_address)
{
    strcpy(__out, inet_ntoa(__ip_address->sin_addr));
}
