#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Bind socket to an IP address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // Port number
    server_address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server listening on port 8080...\n");

    // Accept a client connection
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
    if (client_socket == -1) {
        perror("Acceptance failed");
        exit(1);
    }

    printf("Client connected\n");

    // Receive data from client
    char message[256];
    recv(client_socket, message, sizeof(message), 0);
    printf("Received message from client: %s\n", message);

    // Send a response to the client
    char response[] = "Message received";
    send(client_socket, response, sizeof(response), 0);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}