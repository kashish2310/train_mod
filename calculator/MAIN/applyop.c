double applyOperation(double operand1, double operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        default:
            printf("Error: Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

