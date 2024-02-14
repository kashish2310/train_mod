// Simple XOR encryption function
char* encryption(char text[]) {
    char *encrypted = (char *)malloc(strlen(text) * sizeof(char));
    for (int i = 0; i < strlen(text); i++) {
        encrypted[i] = text[i] ^ ENCRYPTION_KEY;
    }
    return encrypted;
}

// Simple XOR decryption function
char* decryption(char text[]) {
    char *decrypted = (char *)malloc(strlen(text) * sizeof(char));
    for (int i = 0; i < strlen(text); i++) {
        decrypted[i] = text[i] ^ ENCRYPTION_KEY;
    }
    return decrypted;
}
