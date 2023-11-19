#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

int main() {
    int server_socket, new_socket, max_fd, activity, client_sockets[MAX_CLIENTS];
    fd_set read_fds;
    char buffer[BUFFER_SIZE];
    
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    // Create a server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address and bind
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_socket, 5);

    printf("Server listening on port 8080...\n");

    while (1) {
        FD_ZERO(&read_fds);

        FD_SET(server_socket, &read_fds);
        max_fd = server_socket;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            int client_socket = client_sockets[i];

            if (client_socket > 0) {
                FD_SET(client_socket, &read_fds);
                if (client_socket > max_fd) {
                    max_fd = client_socket;
                }
            }
        }

        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("Select error");
        }

        if (FD_ISSET(server_socket, &read_fds)) {
            new_socket = accept(server_socket, (struct sockaddr*)NULL, NULL);

            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            int client_socket = client_sockets[i];

            if (FD_ISSET(client_socket, &read_fds)) {
                int valread = read(client_socket, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // Connection closed by client
                    close(client_socket);
                    client_sockets[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    printf("Client %d: %s\n", i, buffer);
                    write(client_socket, "Message received", 16);
                }
            }
        }
    }

    close(server_socket);
    return 0;
}
