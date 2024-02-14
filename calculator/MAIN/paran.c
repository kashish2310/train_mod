bool hasBalancedParentheses(char *expression) {
    int parenthesesCount = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(')
            parenthesesCount++;
        else if (expression[i] == ')') {
            parenthesesCount--;
            if (parenthesesCount < 0) {
                return false;
            }
        }
    }

    return parenthesesCount == 0;
}
