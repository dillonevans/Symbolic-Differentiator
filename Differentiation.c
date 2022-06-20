#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Differentiation.h"

ExpressionNode* applySumAndDifferenceRule(BinaryExpressionNode node) {
    ExpressionNode* left = differentiate(node.left);
    ExpressionNode* right = differentiate(node.right);
    return initializeBinaryExpression(left, node.op, right);
}

ExpressionNode* applyQuotientRule(BinaryExpressionNode node) {
    ExpressionNode* f = node.left;
    ExpressionNode* fPrime = differentiate(f);
    ExpressionNode* g = node.right;
    ExpressionNode* gPrime = differentiate(g);

    ExpressionNode* lhs = initializeBinaryExpression(fPrime, MultiplicationOperator, g);
    ExpressionNode* rhs = initializeBinaryExpression(f, MultiplicationOperator, gPrime);

    ExpressionNode* numerator = initializeBinaryExpression(lhs, SubtractionOperator, rhs);
    ExpressionNode* denominator = initializeBinaryExpression(g, MultiplicationOperator, g);
    return initializeBinaryExpression(numerator, DivisionOperator, denominator);
}

ExpressionNode* applyProductRule(BinaryExpressionNode node) {
    ExpressionNode* f = node.left;
    ExpressionNode* fPrime = differentiate(f);
    ExpressionNode* g = node.right;
    ExpressionNode* gPrime = differentiate(g);

    ExpressionNode* lhs = initializeBinaryExpression(fPrime, MultiplicationOperator, g);
    ExpressionNode* rhs = initializeBinaryExpression(f, MultiplicationOperator, gPrime);
    return initializeBinaryExpression(lhs, AdditionOperator, rhs);
}

ExpressionNode* applyChainRule(FunctionExpressionNode functionNode) {
    ExpressionNode* fPrimeOfG, * g = functionNode.argument, * gPrime = differentiate(g);

    switch (functionNode.function) {
        case Sin:
            fPrimeOfG = initializeFunctionNode(Cos, g);
            break;
        case Cos:
        {
            ExpressionNode* left = initializeConstantExpression(-1);
            ExpressionNode* right = initializeFunctionNode(Cos, g);
            fPrimeOfG = initializeBinaryExpression(left, MultiplicationOperator, right);
            break;
        }
    }
    return initializeBinaryExpression(fPrimeOfG, MultiplicationOperator, gPrime);
}

ExpressionNode* differentiate(ExpressionNode* node) {
    switch (node->expressionType) {
        case BinaryExpression:
            switch (node->binaryExpressionNode.op) {
                case AdditionOperator:
                case SubtractionOperator:
                    return applySumAndDifferenceRule(node->binaryExpressionNode);
                case MultiplicationOperator:
                    return applyProductRule(node->binaryExpressionNode);
                case DivisionOperator:
                    return applyQuotientRule(node->binaryExpressionNode);
            }
            break;
        case VariableExpression:
            return initializeConstantExpression(1);
        case ConstantExpression:
            return initializeConstantExpression(0);
        case FunctionExpression:
            return applyChainRule(node->functionExpressionNode);
    }
    return NULL;
}