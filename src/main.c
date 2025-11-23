#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "http.h"

#define PORT 8080

int main() {
    signal(SIGPIPE, SIG_IGN);

    int server_fd = start_server(PORT);
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket;

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            continue; 
        }

        char buffer[2048] = {0};
        read(new_socket, buffer, 2048);

        if (strncmp(buffer, "GET / ", 6) == 0) {
            send_file(new_socket, "static/index.html", "text/html");
        } 
        else {
            send_404(new_socket);
        }

        close(new_socket);
    }

    return 0;
}