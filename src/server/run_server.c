/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

void run_server(server_t *server)
{
    int client;
    struct sockaddr_in add;
    socklen_t len = sizeof(add);
    char buffer[1024];

    client = accept(server->socket, (struct sockaddr*)&add, &len);
    recv(client, buffer, sizeof(buffer) - 1, 0);
    printf("%s\n", buffer);
}
