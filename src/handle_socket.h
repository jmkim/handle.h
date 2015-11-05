/*
    handle_socket.h

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

#ifndef _HANDLE_SOCKET_H
#define _HANDLE_SOCKET_H

void    handle_socket_open_tcp  (int *__socket_fd_out);
void    handle_socket_open_udp  (int *__socket_fd_out);
void    handle_socket_open      (int *__socket_fd_out, int __domain, int __type, int __protocol);
void    handle_socket_close     (int __socket_fd);
void    handle_socket_bind      (int __socket_fd, struct sockaddr_in *__addr);
void    handle_socket_listen    (int __socket_fd, int __wait_queue);
void    handle_socket_accept    (int *__socket_client_fd_out, int __socket_server_fd, struct sockaddr_in *__client_addr);
void    handle_socket_connect   (int __socket_fd, struct sockaddr_in *__server_addr);

void    handle_put_address      (struct sockaddr_in *__out, char *__ip_address, int __port);
void    handle_get_address      (char *__out, struct sockaddr_in *__ip_address);

#endif /* !_HANDLE_SOCKET_H */
