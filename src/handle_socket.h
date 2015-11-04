#ifndef _HANDLE_SOCKET_H
#define _HANDLE_SOCKET_H

void    handle_socket_open      (int *__socket_fd_out, struct sockaddr_in *__addr);
void    handle_socket_close     (int __socket_fd);
void    handle_socket_listen    (int __socket_fd, int __wait_queue);
void    handle_socket_accept    (int __socket_fd, struct sockaddr_in *__client_addr, int *__client_addr_len_out);
void    handle_socket_connect   (int __socket_fd, struct sockaddr_in *__server_addr, int __server_addr_len);
void    handle_put_address      (struct sockaddr_in *__out, char *__ip_address, int __port);
void    handle_get_address      (char *__out, struct sockaddr_in *__ip_address);

#endif /* !_HANDLE_SOCKET_H */
