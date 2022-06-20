#ifndef __DIFFERENTIATION_H__
#define __DIFFERENTIATION_H__
#include "AstNode.h"

ExpressionNode* applyProductRule(BinaryExpressionNode node);
ExpressionNode* applySumAndDifferenceRule(BinaryExpressionNode node);
ExpressionNode* applyProductRule(BinaryExpressionNode node);
ExpressionNode* differentiate(ExpressionNode* node);
ExpressionNode* applyChainRule(FunctionExpressionNode node);
ExpressionNode* applyQuotientRule(BinaryExpressionNode node);
#endif // __DIFFERENTIATION_H__