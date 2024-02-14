int authenticate(char *username, char *password) {
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
 
        // Decrypt the stored password for comparison
        decrypt(saved_password);
 
        if (strcmp(username, saved_username) == 0){
            if (strcmp(password, saved_password) == 0) {
                for(int i=0;i<num_clients;i++)
                {
                    if(strcmp(clients[i].username,username) == 0)
                    {
                        fclose(file);
                        pthread_mutex_unlock(&mutex);
                        return 3;
                    }
                }
                fclose(file);
                pthread_mutex_unlock(&mutex);
                return 2; // Authentication successful
            }
            else {
                fclose(file);
                pthread_mutex_unlock(&mutex);
                return 1;
            }
        }
    }
 
    fclose(file);
    pthread_mutex_unlock(&mutex);
    return 0; // Authentication failed
}
 
