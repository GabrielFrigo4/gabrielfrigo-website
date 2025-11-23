#include "http.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void send_404(int socket) {
    char *resp = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
    send(socket, resp, strlen(resp), 0);
}

void send_file(int socket, const char *filename, const char *content_type) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        send_404(socket);
        return;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char header[512];
    sprintf(header, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n", 
        content_type, fsize);
    
    send(socket, header, strlen(header), 0);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, f)) > 0) {
        send(socket, buffer, bytes_read, 0);
    }

    fclose(f);
}