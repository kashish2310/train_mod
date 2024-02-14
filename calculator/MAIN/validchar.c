bool containsValidCharacters(char *expression) {
    for (int i = 0; expression[i] != '\0'; i++) {
        if ((expression[i] >= '0' && expression[i] <= '9') || (expression[i] == '+' || expression[i] == '-' || expression[i] == '.' || expression[i] == '/' || expression[i] == '*' ||
              expression[i] == '(' || expression[i] == ')'))
            return true;
    }
    return false;
}
