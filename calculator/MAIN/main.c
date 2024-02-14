#include"../HDR/hdr.h"


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
