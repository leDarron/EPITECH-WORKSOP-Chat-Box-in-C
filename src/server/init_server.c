/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));

    server->ip_addr = ip_addr;
    server->port = port;

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr_server;
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    addr_server.sin_addr.s_addr = inet_addr(ip_addr);
    bind(server->socket, (const struct sockaddr*) &addr_server, sizeof(addr_server));
    listen(server->socket, FD_SETSIZE);

    return server;
}