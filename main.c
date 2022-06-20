#include <stdlib.h>
#include <stdio.h>
#include "AstNode.h"
#include "Differentiation.h"

int main()
{
    char variableName[] = "x";
    ExpressionNode* x = intializeVariableNode(variableName);
    ExpressionNode* cos = initializeFunctionNode(Cos, x);
    ExpressionNode* sin = initializeFunctionNode(Sin, x);
    ExpressionNode* sinOverCos = initializeBinaryExpression(sin, DivisionOperator, cos);
    ExpressionNode* derivative = differentiate(sinOverCos);
    printExpression(derivative);
}


