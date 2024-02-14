bool isValidFirstCharacter(char *expression) {
    if (expression[0] == '\0') {
        return false;
    }

    return ((expression[0] >= '0' && expression[0] <= '9') || (expression[0] == '-'));
}

