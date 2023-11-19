#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    char server_ip[] = "127.0.0.1";
    int server_port = 8080;
    struct sockaddr_in server_addr;
    char message[1024];

    // Create a client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter a message: ");
        fgets(message, sizeof(message), stdin);
        
        // Send the message to the server
        send(client_socket, message, strlen(message), 0);

        // Receive a response from the server
        memset(message, 0, sizeof(message));
        recv(client_socket, message, sizeof(message), 0);
        printf("Server: %s\n", message);
    }

    close(client_socket);
    return 0;
}
