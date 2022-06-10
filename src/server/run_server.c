/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

int handle_client(int client)
{
    char buffer[1024];

    if (recv(client, buffer, sizeof(buffer) - 1, 0)) {
        close(client);
        return -1;
    }
    printf("%s\n", buffer);
    return 0;
}

void accept_client(server_t *server)
{
    int client;
    struct sockaddr_in add;
    socklen_t len = sizeof(add);

    client = accept(server->socket, (struct sockaddr*)&add, &len);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->fd_array[i] == 0) {
            server->fd_array[i] = client;
            break;
        }
    }
}

void run_server(server_t *server)
{
    server->fd_array = malloc(sizeof(int) * FD_SETSIZE);
    for (int i = 0; i < FD_SETSIZE; i++)
        server->fd_array[i] = 0;
    while (1)
    {
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        FD_SET(server->socket, &server->readfds);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (server->fd_array[i] != 0) {
                FD_SET(server->fd_array[i], &server->readfds);
                FD_SET(server->fd_array[i], &server->writefds);
            }
        }
        select(FD_SETSIZE, &server->readfds, &server->writefds, NULL, NULL);
        if (FD_ISSET(server->socket, &server->readfds))
            accept_client(server);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(server->fd_array[i], &server->readfds)) {
                if (handle_client(server->fd_array[i]) == -1)
                    break;
            }
        }
    }
    close(server->socket);
}
