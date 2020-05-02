#include <sstream>
#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <iterator>
#include "ExpressionManagerInterface.h"
#include "ExpressionManager.h"

ExpressionManager::ExpressionManager(void) {}
ExpressionManager::~ExpressionManager(void) {}

/** Return the integer value of the infix expression */
int ExpressionManager::value(void) {
	stack<int> operandStack;
	istringstream tokens(postExp);
	char nextChar;
	int answer = 0;
	while (tokens >> nextChar) {
		if (isdigit(nextChar)) {
			tokens.putback(nextChar);
			int value;
			tokens >> value;
			operandStack.push(value);
		}
		else {
			int result = eval_op(nextChar, operandStack);
			operandStack.pop();
			operandStack.pop();
			operandStack.push(result);
		}
	}
	if (operandStack.size() == 1) {
		int temp = operandStack.top();
		operandStack.pop();
		answer = temp;
		return answer;
	}
	return -99;		// return error
}

int ExpressionManager::eval_op(char op, stack<int> stack) {
	if (stack.empty()) return -99;
	int rhs = stack.top();
	stack.pop();
	if (stack.empty()) return -99;
	int lhs = stack.top();
	stack.pop();
	int result = 0;
	switch (op) {
	case '+': result = lhs + rhs;
		break;
	case '-': result = lhs - rhs;
		break;
	case '*': result = lhs * rhs;
		break;
	case '/': result = lhs / rhs;
		break;
	case '%': result = lhs % rhs;
		break;
	}
	return result;
}


/** Return the infix items from the expression
	Throw an error if not a valid infix expression as follows:
	First check to see if the expression is balanced ("Unbalanced"),
	then throw the appropriate error immediately when an error is found
	(ie., "Missing Operand", "Illegal Operator", "Missing Operator") */
string ExpressionManager::infix(void) {
	// case 1 - unbalanced
	if (!isBalanced(expression_)) {
		throw int(1);
		return "";		// don't return anything
	}
	// case 2 - illegal operator
	for (unsigned int i = 0; i < inFix_.size(); ++i) {
		if (!isalnum(inFix_[i][0]) && OPEN.find(inFix_[i][0]) == string::npos && CLOSE.find(inFix_[i][0]) == string::npos && OPERATORS.find(inFix_[i][0]) == string::npos) {
			throw char('e');
			return "";
		}
	}
	// case 3 - missing operand
	if (!isNumber(inFix_.at(0)) && !isOpen(inFix_.at(0)[0]) && !isClose(inFix_.at(0)[0])) {		// test if first token isn't a number or parentheses
		throw string("error");
		return "";
	}
	int numOperands = 0;		// test if there is one more operand than operators
	int numOperators = 0;
	for (unsigned int i = 0; i < inFix_.size(); ++i) {
		if (isNumber(inFix_.at(i))) ++numOperands;
		if (isOperator(inFix_.at(i)[0])) ++numOperators;
	}
	if (numOperands != numOperators + 1) {
		throw string("error");
		return "";
	}
	for (unsigned int i = 0; i < inFix_.size() - 1; ++i) {		// test if there are multiple operators in a row
		if (isOperator(inFix_.at(i)[0]) && isOperator(inFix_.at(i + 1)[0])) {
			throw string("error");
			return "";
		}
	}
	// case 4 - missing operator
	for (unsigned int i = 0; i < inFix_.size() - 1; ++i) {		// test if there are multiple numbers in a row
		if (isNumber(inFix_.at(i)) && isNumber(inFix_.at(i + 1))) {
			throw double(1.0);
			return "";
		}
	}
	return toString();
}

/** Return a postfix representation of the infix expression */
string ExpressionManager::postfix(void) {
	stack<char> operatorStack;
	string post = "";
	istringstream infixTokens(expression_);
	string nextToken;
	while (infixTokens >> nextToken) {
		if (isalnum(nextToken[0])) {
			post += nextToken;
			post += " ";
		}
		else {
			if (operatorStack.empty()) {
				operatorStack.push(nextToken[0]);
			}
			else if (isOpen(nextToken[0])) {
				operatorStack.push(nextToken[0]);
			}
			else if (isClose(nextToken[0])) {
				while (!isOpen(operatorStack.top())) {
					post += operatorStack.top();
					post += " ";
					operatorStack.pop();
				}
				operatorStack.pop();
			}
			else {
				if (precedence(nextToken[0]) > precedence(operatorStack.top())) {
					operatorStack.push(nextToken[0]);
				}
				else {
					while (!operatorStack.empty() && (precedence(nextToken[0]) <= precedence(operatorStack.top()))) {
						post += operatorStack.top();
						post += " ";
						operatorStack.pop();
					}
					operatorStack.push(nextToken[0]);
				}
			}
		}
	}
	while (!operatorStack.empty()) {
		char op = operatorStack.top();
		operatorStack.pop();
		post += op;
		post += " ";
	}
	postExp = post;
	return post;
}

bool ExpressionManager::isBalanced(const string& expression) {
	stack<char> s;
	bool balanced = true;
	string::const_iterator iter = expression.begin();
	while (balanced && (iter != expression.end())) {
		char nextChar = *iter;
		if (isOpen(nextChar)) s.push(nextChar);
		else {
			if (isClose(nextChar)) {
				if (s.empty()) balanced = false;
				else {
					char topChar = s.top();
					s.pop();
					balanced = (OPEN.find(topChar) == CLOSE.find(nextChar));
				}
			}
		}
		++iter;
	}
	return balanced && s.empty();
}

