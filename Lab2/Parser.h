#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "Token.h"
using namespace std;

class Parser {
   private:
    vector<Token> tokenVctr;

   public:
    Parser(vector<Token> lexerTokens) {
        tokenVctr = lexerTokens;
    }
    bool peek(tokenType expectedToken) {
        Token currentToken = tokenVctr.front();

        if (currentToken.getType() == expectedToken) {
            return true;
        } else {
            return false;
        }
    }
    void advance() {
        tokenVctr.erase(tokenVctr.begin());
    }
    void match(tokenType expectedToken) {
        Token currentToken = tokenVctr.front();

        if (currentToken.getType() == expectedToken) {
            advance();
        } else {
            throw currentToken;
        }
    }
    void parse() {
        try {
            parseDatalogProgram();
        } catch (Token badToken) {
            cerr << "Failure!\n  " << badToken.toString() << "\n";
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
        cout << "Success!\n";
        cout << toString();  // FIXME
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
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        parseIdList();
        match(RIGHT_PAREN);
    }
    void parseFact() {
        // fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        parseStringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }
    void parseRule() {
        // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
        parseHeadPredicate();
        match(COLON_DASH);
        parsePredicate();
        parsePredicateList();
        match(PERIOD);
    }
    void parseQuery() {
        // query	        ->      predicate Q_MARK
        parsePredicate();
        match(Q_MARK);
    }
    /* SECTION 3 */
    void parseHeadPredicate() {
        // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        parseIdList();
        match(RIGHT_PAREN);
    }
    void parsePredicate() {
        // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
        match(ID);
        match(LEFT_PAREN);
        parseParameter();
        parseParameterList();
        match(RIGHT_PAREN);
    }
    /* SECTION 4 */
    void parsePredicateList() {
        // predicateList	->	COMMA predicate predicateList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            parsePredicate();
            parsePredicateList();
        }
    }
    void parseParameterList() {
        // parameterList	-> 	COMMA parameter parameterList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            parseParameter();
            parseParameterList();
        }
    }
    void parseStringList() {
        // stringList	-> 	COMMA STRING stringList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            match(STRING);
            parseStringList();
        }
    }
    void parseIdList() {
        // idList  	-> 	COMMA ID idList | lambda
        if (peek(COMMA)) {
            match(COMMA);
            match(ID);
            parseIdList();
        }
    }
    /* SECTION 5 */
    void parseParameter() {
        // parameter	->	STRING | ID | expression
        if (peek(STRING)) {
            match(STRING);
        }
        if (peek(ID)) {
            match(ID);
        }
        if (peek(LEFT_PAREN)) {
            parseExpression();
        }
    }
    void parseExpression() {
        // expression	->	LEFT_PAREN parameter operator parameter RIGHT_PAREN
        match(LEFT_PAREN);
        parseParameter();
        parseOperator();
        parseParameter();
        match(RIGHT_PAREN);
    }
    void parseOperator() {
        // operator	->	ADD | MULTIPLY
        if (peek(ADD)) {
            match(ADD);
        }
        if (peek(MULTIPLY)) {
            match(MULTIPLY);
        }
    }
    string toString() const {
        string tokenStr = " Test Vector:\n";
        for (unsigned int i = 0; i < tokenVctr.size(); i++) {
            tokenStr += tokenVctr.at(i).toString() + "\n";
        };
        tokenStr += "Total Tokens = " + to_string(tokenVctr.size()) + "\n";
        return tokenStr;
    }
};

#endif