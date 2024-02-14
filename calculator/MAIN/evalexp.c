double evaluateExpression(const char *expression) {
    OperandStack operandStack;
    OperatorStack operatorStack;
    initializeOperandStack(&operandStack);
    initializeOperatorStack(&operatorStack);

    while (*expression) {
        if (isspace(*expression)) {
            // Skip whitespace
            expression++;
        } else if (isdigit(*expression) || (*expression == '.' && isdigit(*(expression + 1)))) {
            // If the current character is a digit or a dot (for decimals), parse the operand
            double operand = strtod(expression, (char **)&expression);
            pushOperandStack(&operandStack, operand);
        } else if (isOperator(*expression)) {
            // If the current character is an operator
            while (operatorStack.top >= 0 && getPrecedence(operatorStack.data[operatorStack.top]) >= getPrecedence(*expression)) {
                // Pop and evaluate operators with higher or equal precedence
                double operand2 = popOperandStack(&operandStack);
                double operand1 = popOperandStack(&operandStack);
                char op = popOperatorStack(&operatorStack);
                double result = applyOperation(operand1, operand2, op);
                pushOperandStack(&operandStack, result);
            }
            // Push the current operator onto the operator stack
            pushOperatorStack(&operatorStack, *expression);
            expression++;
        } else if (*expression == '(') {
            // If the current character is an open parenthesis, push it onto the operator stack
            pushOperatorStack(&operatorStack, *expression);
            expression++;
        } else if (*expression == ')') {
            // If the current character is a closing parenthesis
            while (operatorStack.top >= 0 && operatorStack.data[operatorStack.top] != '(') {
                // Pop and evaluate operators until an open parenthesis is encountered
                double operand2 = popOperandStack(&operandStack);
                double operand1 = popOperandStack(&operandStack);
                char op = popOperatorStack(&operatorStack);
                double result = applyOperation(operand1, operand2, op);
                pushOperandStack(&operandStack, result);
            }
            // Pop the open parenthesis from the operator stack
            popOperatorStack(&operatorStack);
            expression++;
        } else {
            // Invalid character
            printf("Error: Invalid character: %c\n", *expression);
            exit(EXIT_FAILURE);
        }
    }

    // Process any remaining operators in the stacks
    while (operatorStack.top >= 0) {
        double operand2 = popOperandStack(&operandStack);
        double operand1 = popOperandStack(&operandStack);
        char op = popOperatorStack(&operatorStack);
        double result = applyOperation(operand1, operand2, op);
        pushOperandStack(&operandStack, result);
    }

    // The result should be on top of the operand stack
    return popOperandStack(&operandStack);
}

