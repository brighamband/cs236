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
    void advance() {
        tokenVctr.erase(tokenVctr.begin());
    }
    void match(tokenType expectedToken) {
        tokenType currentToken = tokenVctr.front().getType();

        if (currentToken == expectedToken) {
            advance();
        } else {
            throw currentToken;
        }
    }
    void parse() {
        try {
            parseDatalogProgram();
        } catch (tokenType badToken) {
            Token token;
            cerr << "Bad token: " << token.typeToString(badToken) << endl;
        }
    }
    void parseDatalogProgram() {
        // datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
        match(SCHEMES);
        match(COLON);
        match(COLON);
        cout << toString();
        // cout << "done parsing datalogProgram." << endl;
        // parseScheme();
    }
    /* SECTION 1 */
    void parseSchemeList() {
        // schemeList	->	scheme schemeList | lambda
    }
    void parseFactList() {
        // factList	->	fact factList | lambda
    }
    void parseRuleList() {
        // ruleList	->	rule ruleList | lambda
    }
    void parseQueryList() {
        // queryList	->	query queryList | lambda
    }
    /* SECTION 2 */
    void parseScheme() {
        throw 1;
        cout << "done parsing scheme." << endl;
        parseHeadPredicate();
    }
    void parseFact() {
        // fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    }
    void parseRule() {
        // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    }
    void parseQuery() {
        // query	        ->      predicate Q_MARK
    }
    /* SECTION 3 */
    void parseHeadPredicate() {
        // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
        parseIdList();
    }
    void parsePredicate() {
        // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    }
    /* SECTION 4 */
    void parsePredicateList() {
        // predicateList	->	COMMA predicate predicateList | lambda
    }
    void parseParameterList() {
        // parameterList	-> 	COMMA parameter parameterList | lambda
    }
    void parseStringList() {
        // stringList	-> 	COMMA STRING stringList | lambda
    }
    void parseIdList() {
        // idList  	-> 	COMMA ID idList | lambda
        cout << "end of parsing." << endl;
    }
    /* SECTION 5 */
    void parseParameter() {
        // parameter	->	STRING | ID | expression
    }
    void parseExpression() {
        // expression	->	LEFT_PAREN parameter operator parameter RIGHT_PAREN
    }
    void parseOperator() {
        // operator	->	ADD | MULTIPLY
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