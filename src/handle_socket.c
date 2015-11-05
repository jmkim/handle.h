/*
    handle_socket.c

    Author: Jongmin Kim <jmkim@pukyong.ac.kr>
    Written on November 4, 2015

    Revision history
    1. November 5, 2015
        * (Fixed)   `accept()' returns the file descriptor, but is missing in `handle_socket_accept()'.
    2. November 5, 2015
        * (Fixed)   `bind()' returns -1 in `handle_socket_open()'.
        * (Added)   `handle_socket_open_tcp()' and `handle_socket_open_udp()'.
        * (Changed) Now you can set protocol manually using `handle_socket_open()'.
                    Old one is moved to `handle_socket_open_tcp()'.
    3. November 5, 2015
        * (Fixed)   `accept()' returns -1 in `handle_socket_accept()'.
                    `connect()' returns -1 in `handle_socket_connect()'.
        * (Changed) `handle_socket_bind()' now seperated from `handle_socket_open()'.
                    Length(sizeof-needed) argument removed.
*/

#include <string.h>
#include <arpa/inet.h>

#include "./handle_common.h"
#include "./handle_socket.h"

void handle_socket_open_tcp(int *__socket_fd_out)
{
    return handle_socket_open(__socket_fd_out, PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void handle_socket_open_udp(int *__socket_fd_out)
{
    return handle_socket_open(__socket_fd_out, PF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

void handle_socket_open(int *__socket_fd_out, int __domain, int __type, int __protocol)
{
    int socket_fd = socket(__domain, __type, __protocol);
    if(socket_fd == -1) { handle_error("handle_socket_open", "socket() failed to open."); return; }
    *__socket_fd_out = socket_fd;
}

void handle_socket_close(int __socket_fd)
{
    close(__socket_fd);
}

void handle_socket_bind(int __socket_fd, struct sockaddr_in *__addr)
{
    if(bind(__socket_fd, (struct sockaddr *)__addr, sizeof(struct sockaddr_in)) == -1)
    { handle_error("handle_socket_bind", "bind() failed."); return; }
}

void handle_socket_listen(int __socket_fd, int __wait_queue)
{
    if(listen(__socket_fd, __wait_queue) == -1)
    { handle_error("handle_socket_listen", "listen() failed."); return; }
}

void handle_socket_accept(int *__socket_client_fd_out, int __socket_server_fd, struct sockaddr_in *__client_addr)
{
    int client_addr_len = sizeof(struct sockaddr_in);
    int socket_client_fd = accept(__socket_server_fd, (struct sockaddr *)__client_addr, &client_addr_len);
    if(socket_client_fd == -1) { handle_error("handle_socket_accept", "accept() failed."); return; }
    *__socket_client_fd_out = socket_client_fd;
}

void handle_socket_connect(int __socket_fd, struct sockaddr_in *__server_addr)
{
    if(connect(__socket_fd, (struct sockaddr *)__server_addr, sizeof(struct sockaddr_in)) == -1)
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
