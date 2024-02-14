void register_client(char *username, char *password) {
    pthread_mutex_lock(&mutex);
    FILE *file = fopen(REGISTRATION_FILE, "a");
    if (file == NULL) {
        perror("Error opening registration file");
        exit(EXIT_FAILURE);
    }
 
    // Encrypt the password before storing
    encrypt(password);
 
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    pthread_mutex_unlock(&mutex);
}
 
