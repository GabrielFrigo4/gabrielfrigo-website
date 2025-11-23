#ifndef HTTP_H
#define HTTP_H

void send_file(int socket, const char *filename, const char *content_type);
void send_404(int socket);

#endif