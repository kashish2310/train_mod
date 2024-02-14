#include"../../inc/server_util.h"
#include"encrypt_decrypt.c"
#include"authenticate.c"
#include"register_client.c"
#include"handle_client.c"


int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
 
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }
 
    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.5");
    server_addr.sin_port = htons(11111); // Port number
 
    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in bind");
        exit(EXIT_FAILURE);
    }
 
    // Listen for connections
    if (listen(server_socket, 5) < 0) {
        perror("Error in listen");
        exit(EXIT_FAILURE);
    }
 
    printf("Server is listening...\n");
 
    while (1) {
        // Accept connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Error in accept");
            exit(EXIT_FAILURE);
        }
 
        printf("[::]: New client connected\n");
 
        char buffer[MAX_MSG_LEN]="::|New client connected";
        for (int i = 0; i < num_clients; i++) {
            if (clients[i].socket != client_socket) {
                send(clients[i].socket, buffer, sizeof(buffer), 0);
            }
        }
 
        // Handle client in a separate thread
        pthread_t tid;
        int *client_sock = malloc(1);
        *client_sock = client_socket;
        if (pthread_create(&tid, NULL, handle_client, (void *)client_sock) < 0) {
            perror("Error creating thread");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
        pthread_detach(tid);
    }
 
    return 0;
}
