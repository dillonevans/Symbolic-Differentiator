#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AstNode.h"

ExpressionNode* initializeBinaryExpression(ExpressionNode* left, BinaryOperator op, ExpressionNode* right) {
    ExpressionNode* node = malloc(sizeof(*node));
    node->expressionType = BinaryExpression;
    node->binaryExpressionNode.left = left;
    node->binaryExpressionNode.op = op;
    node->binaryExpressionNode.right = right;
    return node;
}

ExpressionNode* initializeFunctionNode(Function function, ExpressionNode* argument) {
    ExpressionNode* node = malloc(sizeof(*node));
    node->expressionType = FunctionExpression;
    node->functionExpressionNode.function = function;
    node->functionExpressionNode.argument = argument;
    return node;
}

ExpressionNode* initializeConstantExpression(double value) {
    ExpressionNode* node = malloc(sizeof(*node));
    node->expressionType = ConstantExpression;
    node->literalExpressionNode.type = Integer;
    node->literalExpressionNode.value = value;
    return node;
}

ExpressionNode* intializeVariableNode(char* name) {
    ExpressionNode* node = malloc(sizeof(*node));
    node->expressionType = VariableExpression;
    strcpy(node->variableExpressionNode.name, name);
    return node;
}

void printExpressionHelper(ExpressionNode* root)
{
    switch (root->expressionType) {
        case BinaryExpression:
            printf("(");
            printExpressionHelper(root->binaryExpressionNode.left);
            switch (root->binaryExpressionNode.op) {
                case AdditionOperator:
                    printf(" + ");
                    break;
                case SubtractionOperator:
                    printf(" - ");
                    break;
                case MultiplicationOperator:
                    printf("");
                    break;
                case DivisionOperator: // Todo: Implement quotient rule
                    printf(" / ");
                    break;
            }
            printExpressionHelper(root->binaryExpressionNode.right);
            printf(")");
            break;
        case VariableExpression:
            printf("%s", root->variableExpressionNode.name);
            break;
        case ConstantExpression:
            printf("%d", (int)(root->literalExpressionNode.value));
            break;
        case FunctionExpression:
            switch (root->functionExpressionNode.function) {
                case Sin:
                    printf("Sin");
                    break;
                case Cos:
                    printf("Cos");
                    break;
            }
            printf("(");
            printExpressionHelper(root->functionExpressionNode.argument);
            printf(")");
            break;
    }
    return;
}

void printExpression(ExpressionNode* root) {
    printExpressionHelper(root);
    printf("\n");
}