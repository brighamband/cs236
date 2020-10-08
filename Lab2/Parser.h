#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "DatalogProgram.h"
#include "Predicate.h"
#include "Token.h"
using namespace std;

class Parser {
   private:
    vector<Token> tokenVctr;
    Token currentToken;
    string tempPredName;
    vector<Predicate> tempPredVctr;
    vector<Parameter> tempParamVctr;
    DatalogProgram datalog;

   public:
    Parser(vector<Token> lexerTokens) {
        tokenVctr = lexerTokens;
        currentToken = tokenVctr.front();
    }
    // DatalogProgram datalog;
    bool peek(tokenType expectedToken) {
        if (currentToken.getType() == expectedToken) {
            return true;
        } else {
            return false;
        }
    }
    void advance() {
        tokenVctr.erase(tokenVctr.begin());
        currentToken = tokenVctr.front();
    }
    void match(tokenType expectedToken) {
        if (currentToken.getType() == expectedToken) {
            advance();
        } else {
            throw currentToken;
        }
    }
    bool parse() {
        try {
            parseDatalogProgram();
            cout << "Success!\n";
            cout << datalog.toString();
            return true;
        } catch (Token badToken) {
            cerr << "Failure!\n  " << badToken.toString() << "\n";
            return false;
        }
    }
    void parseDatalogProgram() {
        // datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
        match(SCHEMES);
        match(COLON);
        parseScheme();
        parseSchemeList();
        match(FACTS);
        match(COLON);
        parseFactList();
        match(RULES);
        match(COLON);
        parseRuleList();
        match(QUERIES);
        match(COLON);
        parseQuery();
        parseQueryList();
        match(END_OF_FILE);
    }
    /* SECTION 1 */
    void parseSchemeList() {
        // schemeList	->	scheme schemeList | lambda
        if (peek(ID)) {
            parseScheme();
            parseSchemeList();
        }
    }
    void parseFactList() {
        // factList	->	fact factList | lambda
        if (peek(ID)) {
            parseFact();
            parseFactList();
        }
    }
    void parseRuleList() {
        // ruleList	->	rule ruleList | lambda
        if (peek(ID)) {
            parseRule();
            parseRuleList();
        }
    }
    void parseQueryList() {
        // queryList	->	query queryList | lambda
        if (peek(ID)) {
            parseQuery();
            parseQueryList();
        }
    }
    /* SECTION 2 */
    void parseScheme() {
        // scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
        tempPredName = currentToken.getValue();
        match(ID);
        match(LEFT_PAREN);
        tempParamVctr.push_back(currentToken.getValue());
        match(ID);
        parseIdList();
        match(RIGHT_PAREN);
        Predicate predicate(tempPredName, tempParamVctr);
        datalog.addScheme(predicate);
        tempParamVctr.clear();
    }
    void parseFact() {
        // fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
        tempPredName = currentToken.getValue();
        match(ID);
        match(LEFT_PAREN);
        tempParamVctr.push_back(currentToken.getValue());
        datalog.addDomain(currentToken.getValue());
        match(STRING);
        parseStringList();
        match(RIGHT_PAREN);
        match(PERIOD);
        Predicate predicate(tempPredName, tempParamVctr);
        datalog.addFact(predicate);
        tempParamVctr.clear();
    }
    void parseRule() {
        // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
        parseHeadPredicate();
        Predicate tempHeadPred(tempPredName, tempParamVctr);
        tempParamVctr.clear();
        match(COLON_DASH);
        parsePredicate();
        tempParamVctr.clear();
        parsePredicateList();
        match(PERIOD);
        Rule rule(tempHeadPred, tempPredVctr);
        datalog.addRule(rule);
        tempPredVctr.clear();
        tempParamVctr.clear();
    }
    void parseQuery() {
        // query	        ->      predicate Q_MARK
        parsePredicate();
        match(Q_MARK);
        Predicate predicate(tempPredName, tempParamVctr);
        datalog.addQuery(predicate);
        tempParamVctr.clear();
    }
    /* SECTION 3 */
    void parseHeadPredicate() {
        // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
        tempPredName = currentToken.getValue();
        match(ID);
        match(LEFT_PAREN);
        tempParamVctr.push_back(currentToken.getValue());
        match(ID);
        parseIdList();
        match(RIGHT_PAREN);
    }
    void parsePredicate() {
        // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
        tempPredName = currentToken.getValue();
        match(ID);
        match(LEFT_PAREN);
        Parameter parameter = parseParameter();
        tempParamVctr.push_back(parameter);
        parseParameterList();
        match(RIGHT_PAREN);
        Predicate predicate(tempPredName, tempParamVctr);
        tempPredVctr.push_back(predicate);
    }
    /* SECTION 4 */
    void parsePredicateList() {
        // predicateList	->	COMMA predicate predicateList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            parsePredicate();
            tempParamVctr.clear();
            parsePredicateList();
        }
    }
    void parseParameterList() {
        // parameterList	-> 	COMMA parameter parameterList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            Parameter parameter = parseParameter();
            tempParamVctr.push_back(parameter);
            parseParameterList();
        }
    }
    void parseStringList() {
        // stringList	-> 	COMMA STRING stringList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            tempParamVctr.push_back(currentToken.getValue());
            datalog.addDomain(currentToken.getValue());
            match(STRING);
            parseStringList();
        }
    }
    void parseIdList() {
        // idList  	-> 	COMMA ID idList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            tempParamVctr.push_back(currentToken.getValue());
            match(ID);
            parseIdList();
        }
    }
    /* SECTION 5 */
    Parameter parseParameter() {
        // parameter	->	STRING | ID | expression
        Parameter paramStr(currentToken.getValue());
        if (peek(STRING)) {
            match(STRING);
        }
        if (peek(ID)) {
            match(ID);
        }
        if (peek(LEFT_PAREN)) {
            paramStr.setValue(parseExpression());
        }
        return paramStr;
    }

    string parseExpression() {
        // expression	->	LEFT_PAREN parameter operator parameter RIGHT_PAREN
        string expStr = currentToken.getValue();
        match(LEFT_PAREN);
        Parameter parameter1 = parseParameter();
        expStr += parameter1.toString();
        string operParam = parseOperator();
        expStr += operParam;
        Parameter parameter2 = parseParameter();
        expStr += parameter2.toString() + currentToken.getValue();
        match(RIGHT_PAREN);
        return expStr;
    }
    string parseOperator() {
        // operator	->	ADD | MULTIPLY
        string operStr = currentToken.getValue();
        if (peek(ADD)) {
            match(ADD);
        } else if (peek(MULTIPLY)) {
            match(MULTIPLY);
        } else {
            throw currentToken;
        }
        return operStr;
    }
};

#endif