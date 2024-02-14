void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    free(arg);
 
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
 
top:
    // Receive username
    if (recv(client_socket, username, sizeof(username), 0) <= 0) {
        perror("Error receiving username");
        close(client_socket);
        return NULL;
    }
 
    // Receive password
    if (recv(client_socket, password, sizeof(password), 0) <= 0) {
        perror("Error receiving password");
        close(client_socket);
        return NULL;
    }
 
    // Check if the client wants to register or authenticate
    char choice;
    if (recv(client_socket, &choice, sizeof(choice), 0) <= 0) {
        perror("Error receiving choice");
        close(client_socket);
        return NULL;
    }
 
    if (choice == 'r') { // Register new user
 
        pthread_mutex_lock(&mutex);
        FILE *file = fopen(REGISTRATION_FILE, "r");
        if (file == NULL) {
            perror("Error opening registration file");
            exit(EXIT_FAILURE);
        }
 
        char line[MAX_USERNAME_LEN + MAX_PASSWORD_LEN + 2];
        while (fgets(line, sizeof(line), file) != NULL) {
            char saved_username[MAX_USERNAME_LEN];
            char saved_password[MAX_PASSWORD_LEN];
 
            sscanf(line, "%s %s", saved_username, saved_password);
 
            if(strcmp(saved_username,username) == 0) {
 
                fclose(file);
                pthread_mutex_unlock(&mutex);
                send(client_socket,"11",2,0);
 
                close(client_socket);
                return NULL;
            }
        }
 
        fclose(file);
        pthread_mutex_unlock(&mutex);
        register_client(username, password);
        send(client_socket, "Registration successful.\n", 26, 0);
        close(client_socket);
        return NULL;
 
    } else if (choice == 'a') { // Authenticate user
        int auth_code = authenticate(username,password);
        if (auth_code == 0) {
            send(client_socket,"00",2,0);
            goto top;
        }
        if (auth_code == 1) {
            send(client_socket,"10",2,0);
            goto top;
        }
        if (auth_code == 3) {
            send(client_socket,"01",2,0);
            goto top;
        }
        if (auth_code == 2) {
            send(client_socket, "Authentication successful. You are now in the chat.\n", 50, 0);
            // Add client to the list
            pthread_mutex_lock(&mutex);
            struct Client new_client;
            new_client.socket = client_socket;
            strncpy(new_client.username, username, MAX_USERNAME_LEN);
            clients[num_clients++] = new_client;
            pthread_mutex_unlock(&mutex);
 
            printf("[%s]: == Logged into chat ==\n",username);
 
            char buffer[MAX_MSG_LEN+MAX_USERNAME_LEN+1];
 
            sprintf(buffer,"%s|%s",username,"== Logged into chat ==");
            // Broadcast message to all other clients
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < num_clients; i++) {
                if (clients[i].socket != client_socket) {
                    send(clients[i].socket, buffer, sizeof(buffer), 0);
                }
            }
            pthread_mutex_unlock(&mutex);
 
        } else {
            send(client_socket, "Authentication failed. Disconnecting.\n", 40, 0);
            close(client_socket);
            return NULL;
        }
    } else {
        perror("Invalid choice");
        close(client_socket);
        return NULL;
    }
 
 
    char message[MAX_MSG_LEN];
    while (1) {
        // Receive message from client
//      char message[MAX_MSG_LEN];
        memset(message,0,sizeof(message));
        int bytes_received = recv(client_socket,message,sizeof(message),0);
        if (bytes_received <= 0) {
            printf("[%s]: == Disconnected ==\n", username);
            pthread_mutex_lock(&mutex);
            // Remove client from the list
            for (int i = 0; i < num_clients; i++) {
                if (clients[i].socket == client_socket) {
                    for (int j = i; j < num_clients - 1; j++) {
                        clients[j] = clients[j + 1];
                    }
                    num_clients--;
                    break;
                }
            }
            pthread_mutex_unlock(&mutex);
 
 
            char buffer[MAX_MSG_LEN+MAX_USERNAME_LEN+1];
 
            sprintf(buffer,"%s|%s",username,"== Disconnected ==");
            // Broadcast message to all other clients
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < num_clients; i++) {
                if (clients[i].socket != client_socket) {
                    send(clients[i].socket, buffer, sizeof(buffer), 0);
                }
            }
            pthread_mutex_unlock(&mutex);
 
            close(client_socket);
            return NULL;
        }
 
        message[bytes_received] = '\0';
 
        // Print the message on the server
        printf("[%s]: %s\n", username, message);
 
        char buffer[MAX_MSG_LEN+MAX_USERNAME_LEN+1];
 
        sprintf(buffer,"%s|%s",username,message);
        // Broadcast message to all other clients
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < num_clients; i++) {
            if (clients[i].socket != client_socket) {
                send(clients[i].socket, buffer, sizeof(buffer), 0);
            }
        }
        pthread_mutex_unlock(&mutex);
    }
 
    return NULL;
}
