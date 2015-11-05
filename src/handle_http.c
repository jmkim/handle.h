/*
    handle_http.c

    Author: Jongmin Kim <jmkim@pukyong.ac.kr>
    Written on November 5, 2015
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "./handle_http.h"

void handle_http_header(int __socket_client)
{
    char buffer[100];

    handle_http_header_date(buffer, sizeof(buffer));
    handle_http_header_output(__socket_client, "Date", buffer);

    handle_http_header_server(buffer);
    handle_http_header_output(__socket_client, "Server", buffer);

    handle_http_header_output(__socket_client, "Last-Modified", "Thu, 05 Nov 2015 11:28:41 GMT");
    handle_http_header_output(__socket_client, "Content-Type", "text/html; charset=UTF-8");
    handle_http_header_output(__socket_client, "Connection", "close");
    handle_http_header_output(__socket_client, "Accept-Ranges", "bytes");

    write(__socket_client, "\n", sizeof(char) * 1 + 1);
}

void handle_http_header_output(int __socket_client, char *__key, char *__value)
{
    char buffer[HANDLE_HTTP_BUFFER_SIZE];
    sprintf(buffer, "%s: %s\n", __key, __value);
    write(__socket_client, buffer, strlen(buffer));
}

void handle_http_header_date(char *__out, size_t __out_len)
{
    time_t ct = time(NULL);
    struct tm *gmt = gmtime(&ct);
    strftime(__out, __out_len, "%a, %d %b %Y %H:%M:%S GMT", gmt);
}

void handle_http_header_server(char *__out)
{
#if defined(_WIN32) || defined(_WIN64)
    const char *os = "Socketserver (Windows)";
#else 
#ifdef __gnu_linux__
    const char *os = "Socketserver (Linux)";
#else
    const char *os = "Socketserver (Unknown)";
#endif /* __gnu_linux__ */
#endif /* _WIN32 || _WIN64 */
    strcpy(__out, os);
}

void handle_http_header_status(int __socket_client, int __status_code)
{
    char message[200];
    switch(__status_code)
    {
    case 100: { strcpy(message, "Continue");                         break; }
    case 101: { strcpy(message, "Switching Protocols");              break; }
    case 200: { strcpy(message, "OK");                               break; }
    case 201: { strcpy(message, "Created");                          break; }
    case 202: { strcpy(message, "Accepted");                         break; }
    case 203: { strcpy(message, "Non-Authoritative Information");    break; }
    case 204: { strcpy(message, "No Content");                       break; }
    case 205: { strcpy(message, "Reset Content");                    break; }
    case 206: { strcpy(message, "Partial Content");                  break; }
    case 300: { strcpy(message, "Multiple Choices");                 break; }
    case 301: { strcpy(message, "Moved Permanently");                break; }
    case 302: { strcpy(message, "Found");                            break; }
    case 303: { strcpy(message, "See Other");                        break; }
    case 304: { strcpy(message, "Not Modified");                     break; }
    case 305: { strcpy(message, "Use Proxy");                        break; }
    case 307: { strcpy(message, "Temporary Redirect");               break; }
    case 400: { strcpy(message, "Bad Request");                      break; }
    case 401: { strcpy(message, "Unauthorized");                     break; }
    case 402: { strcpy(message, "Payment Required");                 break; }
    case 403: { strcpy(message, "Forbidden");                        break; }
    case 404: { strcpy(message, "Not Found");                        break; }
    case 405: { strcpy(message, "Method Not Allowed");               break; }
    case 406: { strcpy(message, "Not Acceptable");                   break; }
    case 407: { strcpy(message, "Proxy Authentication Required");    break; }
    case 408: { strcpy(message, "Request Time-out");                 break; }
    case 409: { strcpy(message, "Conflict");                         break; }
    case 410: { strcpy(message, "Gone");                             break; }
    case 411: { strcpy(message, "Length Required");                  break; }
    case 412: { strcpy(message, "Precondition Failed");              break; }
    case 413: { strcpy(message, "Request Entity Too Large");         break; }
    case 414: { strcpy(message, "Request-URI Too Large");            break; }
    case 415: { strcpy(message, "Unsupported Media Type");           break; }
    case 416: { strcpy(message, "Requested range not satisfiable");  break; }
    case 417: { strcpy(message, "Expectation Failed");               break; }
    case 500: { strcpy(message, "Internal Server Error");            break; }
    case 501: { strcpy(message, "Not Implemented");                  break; }
    case 502: { strcpy(message, "Bad Gateway");                      break; }
    case 503: { strcpy(message, "Service Unavailable");              break; }
    case 504: { strcpy(message, "Gateway Time-out");                 break; }
    case 505: { strcpy(message, "HTTP Version not supported");       break; }
    }

    char status_code[10];
    sprintf(status_code, "%d", __status_code);

    char buffer[HANDLE_HTTP_BUFFER_SIZE];
    sprintf(buffer, "HTTP/1.1 %d %s\n", __status_code, message);
    write(__socket_client, buffer, strlen(buffer));
}
