#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 1000

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

bool isValidFirstCharacter(char *expression) {
    if (expression[0] == '\0') {
        return false;
    }

    return ((expression[0] >= '0' && expression[0] <= '9') || (expression[0] == '-'));
}

bool containsValidCharacters(char *expression) {
    for (int i = 0; expression[i] != '\0'; i++) {
        if ((expression[i] >= '0' && expression[i] <= '9') || (expression[i] == '+' || expression[i] == '-' || expression[i] == '.' || expression[i] == '/' || expression[i] == '*' ||
              expression[i] == '(' || expression[i] == ')'))
            return true;
    }
    return false;
}

typedef struct {
    double data[MAX_SIZE];
    int top;
} OperandStack;

void initializeOperandStack(OperandStack *stack) {
    stack->top = -1;
}

void pushOperandStack(OperandStack *stack, double value) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = value;
    } else {
        printf("Operand stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

double popOperandStack(OperandStack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        printf("Operand stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

typedef struct {
    double data[MAX_SIZE];
    int top;
} OperatorStack;

void initializeOperatorStack(OperatorStack *stack) {
    stack->top = -1;
}

void pushOperatorStack(OperatorStack *stack, double value) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = value;
    } else {
        printf("Operator stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

double popOperatorStack(OperatorStack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        printf("Operator stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return 0; // Assuming other characters are operands
}

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

int main() {
    char expression[MAX_SIZE];

    printf("Enter a mathematical expression: ");
    scanf("%[^\n]%*c", expression);

    if (containsValidCharacters(expression) && hasBalancedParentheses(expression) && isValidFirstCharacter(expression)) {
        double result = evaluateExpression(expression);
        printf("Result: %lf\n", result);
    } else {
        printf("Invalid expression\n");
    }

    return 0;
}

