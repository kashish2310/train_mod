#include"../../inc/client_util.h"
#include"receive_msg.c"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
 
top:
    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }
 
    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
 
    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connect");
        exit(EXIT_FAILURE);
    }
 
    printf("Connected to server\n");
 
    char choice;
start:
    printf("Do you want to register a new account? (y/n): ");
    scanf(" %c", &choice);
 
    if (choice == 'y' || choice == 'Y') {
        char new_username[MAX_USERNAME_LEN];
        char new_password[MAX_PASSWORD_LEN];
 
        // Get new username and password
        printf("Enter new username: ");
        scanf("%s", new_username);
 
        printf("Enter new password: ");
        scanf("%s", new_password);
 
        // Send registration request to the server
        send(client_socket, new_username, sizeof(new_username), 0);
        send(client_socket, new_password, sizeof(new_password), 0);
        send(client_socket, "r", 1, 0); // Send 'r' to indicate registration
 
        char response[50];
        recv(client_socket, response, sizeof(response), 0);
 
        if(strcmp(response,"11") == 0) {
            printf("        Username already exist\n======Kindly Register or use other account======\n");
 
        } else
        printf("    %s=====Kindly login with new credentials=====\n", response);
    } else {
        char username[MAX_USERNAME_LEN];
        char password[MAX_PASSWORD_LEN];
 
login:
        printf("Enter username: ");
        scanf("%s", username);
 
        printf("Enter password: ");
        scanf("%s", password);
 
        // Send username
        send(client_socket, username, sizeof(username), 0);
        // Send password
        send(client_socket, password, sizeof(password), 0);
        send(client_socket, "a", 1, 0); // Send 'a' to indicate authentication
 
        char response[50];
        recv(client_socket, response, sizeof(response), 0);
        if(strcmp(response,"00") == 0) {
            printf("       Invalid username\n======Kindly Register======\n");
            goto start;
        }
        if(strcmp(response,"10") == 0) {
            printf("       Incorrect password\n======Kindly Retry======\n");
            goto login;
        }
        if(strcmp(response,"01") == 0) {
            printf("       User [%s] already exist\n======Kindly Register or login with different username======\n",username);
            goto start;
        }
        printf("%s\n", response);
 
        // Create a thread to receive messages from the server
        pthread_t tid;
        int *sock = malloc(1);
        *sock = client_socket;
        if (pthread_create(&tid, NULL, receive_messages, (void *)sock) < 0) {
            perror("Error creating thread");
            close(client_socket);
            exit(EXIT_FAILURE);
        }
 
        // Send messages to the server
        char message[MAX_MSG_LEN];
        while (1) {
            char message[MAX_MSG_LEN];
            memset(message,0,sizeof(message));
            //printf("Enter message: ");
 
            fgets(message,sizeof(message),stdin);
            message[strcspn(message,"\n")]=0;
 
            send(client_socket, message, strlen(message), 0);
        }
    }
 
    // Close socket
    close(client_socket);
 
    return 0;
}
