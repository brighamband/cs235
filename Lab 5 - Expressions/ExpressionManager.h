#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H

#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <iterator>
#include "ExpressionManagerInterface.h"
using namespace std;

class ExpressionManager : public ExpressionManagerInterface {
private:
	string expression_;
	string postExp;
	vector<string> inFix_;
	const string OPEN = "([{";		// set of opening parentheses
	const string CLOSE = ")]}";		// set of closing parentheses
	const string OPERATORS = "+-*/%";		// set of operators
	const int PRECEDENCE[5] = { 1, 1, 2, 2, 2 };
public:
	ExpressionManager(void);
	~ExpressionManager(void);

	int value(void);
	int eval_op(char op, stack<int> stack);
	string infix(void);
	string postfix(void);
	bool isBalanced(const string& expression);
	string prefix(void) { return "NOT IMPLEMENTED"; }
	bool isOpen(char ch) { return OPEN.find(ch) != string::npos; }
	bool isClose(char ch) { return CLOSE.find(ch) != string::npos; }
	bool isOperator(char ch) const { return OPERATORS.find(ch) != string::npos; }

	string toString(void) const {
		string vectorToString = "";
		for (unsigned int i = 0; i < inFix_.size(); ++i) {
			vectorToString += inFix_.at(i) + " ";
		}
		return vectorToString;
	}

	void setExpression(string exp) {
		expression_ = exp;

		// also fill inFix_ string vector with expString's values
		istringstream iss(exp);
		vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());
		inFix_ = results;
	}	

	int precedence(char op) const {
		if (OPERATORS.find(op) == string::npos) {
			return 0;
		}
		else {
			return PRECEDENCE[OPERATORS.find(op)];
		}
	}

	bool isNumber(const string& token) {
		string::const_iterator iter = token.begin();
		while (iter != token.end() && std::isdigit(*iter)) ++iter;
		return !token.empty() && iter == token.end();
	}
};

#endif