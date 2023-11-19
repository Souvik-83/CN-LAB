#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // Port number
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    // Send a message to the server
    char message[] = "hello";
    send(client_socket, message, sizeof(message), 0);

    // Receive response from server
    char response[256];
    recv(client_socket, response, sizeof(response), 0);
    printf("Server response: %s\n", response);

    // Close the socket
    close(client_socket);

    return 0;
}