/*
    handle_http.h

    Author: Jongmin Kim <jmkim@pukyong.ac.kr>
    Written on November 5, 2015
*/

#ifndef _HANDLE_HTTP_H
#define _HANDLE_HTTP_H

#ifndef HANDLE_HTTP_BUFFER_SIZE
#define HANDLE_HTTP_BUFFER_SIZE 1000
#endif

void    handle_http_header          (int __socket_client);
void    handle_http_header_output   (int __socket_client, char *__key, char *__value);
void    handle_http_header_date     (char *__out, size_t __out_len);
void    handle_http_header_server   (char *__out);
void    handle_http_header_status   (int __socket_client, int __status_code);

#endif /* ! _HANDLE_HTTP_H */
