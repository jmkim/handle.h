/*
    sample_http_listener.c
    Show IP address of client
    May be following RFC 2616 "HTTP/1.1"

    Author: Jongmin Kim <jmkim@pukyong.ac.kr>
    Written on November 5, 2015
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>
#include <arpa/inet.h>

#include "../src/handle_http.h"
#include "../src/handle_socket.h"


char *log_fname = "./sample_http_listener.log";

void output_html(int __socket_client, char *__ip_address)
{
    char buffer[HANDLE_HTTP_BUFFER_SIZE];
    sprintf(buffer, "<!DOCTYPE html>\n<html>\n<head>\n<title>Your IP is: %s</title>\n</head>\n<body>\n<p>%s</p>\n</body>\n</html>\n", __ip_address, __ip_address);
    write(__socket_client, buffer, strlen(buffer));
}

int main(int argc, char **argv)
{
    if(argc < 2) { fprintf(stderr, "Usage: %s [port]\n", argv[0]); return 1; }

    int socket_server, socket_client;
    struct sockaddr_in address_server, address_client;
    handle_put_address(&address_server, "0.0.0.0", atoi(argv[1]));

    handle_socket_open_tcp(&socket_server);
    handle_socket_bind(socket_server, &address_server);
    handle_socket_listen(socket_server, 10);
    while(true)
    {
        handle_socket_accept(&socket_client, socket_server, &address_client);

        char request[HANDLE_HTTP_BUFFER_SIZE];
        read(socket_client, request, sizeof(request));
        if(! strncmp(request, "GET", 3))
        {
            handle_http_header_status(socket_client, 200);
            handle_http_header(socket_client);

            socklen_t address_len = sizeof(address_client);

            char remote_addr[HANDLE_HTTP_BUFFER_SIZE];
            getpeername(socket_client, (struct sockaddr *)&address_client, &address_len);
            handle_get_address(remote_addr, &address_client);

            char time_local[HANDLE_HTTP_BUFFER_SIZE];
            time_t ct = time(NULL);
            struct tm *lt = localtime(&ct);
            strftime(time_local, sizeof(time_local), "%d/%b/%Y:%H:%M:%S %z", lt);

            FILE *log_f = fopen(log_fname, "a");
            int status = 0, byte_sent = 0;
            char remote_user[] = "-", http_referer[] = "-", http_user_agent[] = "-";
            fprintf(log_f,
                "%s - %s [%s]"/*\"%s\"*/" %d %d \"%s\" \"%s\"\n"
                , remote_addr
                , remote_user
                , time_local
                //, request
                , status
                , byte_sent
                , http_referer
                , http_user_agent
            );
            fclose(log_f);

            output_html(socket_client, remote_addr);
            handle_socket_close(socket_client);
        }
        else
        {
            handle_http_header_status(socket_client, 400);
            handle_socket_close(socket_client);
        }
    }

    return 0;
}
