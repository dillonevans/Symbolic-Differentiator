#ifndef __ASTNODE_H__
#define __ASTNODE_H__

#define MAX_VARIABLE_NAME_LENGTH 512
typedef struct BinaryExpressionNode BinaryExpressionNode;
typedef struct VariableExpressionNode VariableExpressionNode;
typedef struct ConstantExpressionNode ConstantExpressionNode;
typedef struct FunctionExpressionNode FunctionExpressionNode;
typedef struct ExpressionNode ExpressionNode;

typedef enum BinaryOperator {
    AdditionOperator,
    SubtractionOperator,
    MultiplicationOperator,
    DivisionOperator
} BinaryOperator;

typedef enum Function {
    Sin,
    Cos,
    Tan
} Function;

typedef enum LiteralType {
    Integer,
    Double
} LiteralType;

typedef enum ExpressionType {
    BinaryExpression,
    VariableExpression,
    ConstantExpression,
    FunctionExpression
} ExpressionType;

struct BinaryExpressionNode {
    ExpressionNode* left, * right;
    BinaryOperator op;
};

struct VariableExpressionNode {
    char name[MAX_VARIABLE_NAME_LENGTH];
};

struct ConstantExpressionNode {
    LiteralType type;
    double value;
};

struct FunctionExpressionNode {
    Function function;
    ExpressionNode* argument;
};

struct ExpressionNode {
    ExpressionType expressionType;
    union {
        BinaryExpressionNode binaryExpressionNode;
        ConstantExpressionNode literalExpressionNode;
        VariableExpressionNode variableExpressionNode;
        FunctionExpressionNode functionExpressionNode;
    };
};

ExpressionNode* initializeFunctionNode(Function function, ExpressionNode* argument);
ExpressionNode* initializeConstantExpression(double value);
ExpressionNode* intializeVariableNode(char* name);
ExpressionNode* initializeBinaryExpression(ExpressionNode* left, BinaryOperator op, ExpressionNode* right);
ExpressionNode* fold(ExpressionNode* root);
void printExpression(ExpressionNode* root);

#endif // __ASTNODE_H__