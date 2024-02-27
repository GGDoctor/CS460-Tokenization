// Tokenization
// The objective of this project is to take the second step torwards building an interpreter, tokenizing a file

// This project is developed by the following students:
// Haley Joerger
// Adam Lyday
// Jacob Franco
// Zach Gassner


#include <iostream>
#include <fstream> //Including fstream and string allow us to read in the input file
#include <string>
#include <vector> 
#include <cctype>
#include <algorithm>
using namespace std;


//Defining the different token types
enum TokenType {
    IDENTIFIER,
    INTEGER,
    STRING,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    SEMICOLON,
    COMMA,
    ASSIGNMENT,
    PLUS,
    MINUS,
    DIVIDE,
    ASTERISK,
    MODULO,
    CARAT,
    LT,
    GT,
    LT_EQUAL,
    GT_EQUAL,
    BOOLEAN_AND_OPERATOR,
    BOOLEAN_OR_OPERATOR,
    BOOLEAN_NOT_OPERATOR,
    BOOLEAN_EQUAL,
    BOOLEAN_NOT_EQUAL,
    BOOLEAN_TRUE,
    BOOLEAN_FALSE,
};

vector<char> listOfSymbols = {'(', ')', '[', ']', '{', '}', '\"', '\'', ';', ',', '=', '+', '-', '\\', '*', '%', '^', '>', '<', '&', '|', '!'};



//struct Token
//Store store token information
struct Token {
    TokenType type;
    string character;
};



vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    string currentToken; //Read char by char
    bool inComment = false;
    bool inString = false;
    int lineNumber = 1;

    for (size_t i=0;i < input.size(); ++i) {

        if (inString) {
            Token stringToken;
            stringToken.type = STRING;

            while (input[i] != tokens.back().character[0]) {
                stringToken.character += input[i++];
            }

             

            tokens.push_back(stringToken);
            
        }

        char nextChar = i + 1 < input.size() ? input[i + 1] : 0; 

        Token inputToken;
        switch(input[i]){
            case ' ':
                break;

            case '\n':
                lineNumber++;
                break;

            case '(':
                inputToken.type = LEFT_PARENTHESIS;
                inputToken.character = "(";
                tokens.push_back(inputToken);
                break;
                
            case ')':
                inputToken.type = RIGHT_PARENTHESIS;
                inputToken.character = ")";
                tokens.push_back(inputToken);
                break;

            case '[':
                inputToken.type = LEFT_BRACKET;
                inputToken.character = "[";
                tokens.push_back(inputToken);
                break;

            case ']':
                inputToken.type = RIGHT_BRACKET;
                inputToken.character = "]";
                tokens.push_back(inputToken);
                break;

            case '{':
                inputToken.type = LEFT_BRACE;
                inputToken.character = "{";
                tokens.push_back(inputToken);
                break;

            case '}':
                inputToken.type = RIGHT_BRACE;
                inputToken.character = "}";
                tokens.push_back(inputToken);
                break;

            case '"':
                inputToken.type = DOUBLE_QUOTE;
                inputToken.character = "\"";
                tokens.push_back(inputToken);
                inString = !inString;
                break;

            case '\'':
                inputToken.type = SINGLE_QUOTE;
                inputToken.character = "\'";
                tokens.push_back(inputToken);
                inString = !inString;
                break;

            case ';':
                inputToken.type = SEMICOLON;
                inputToken.character = ";";
                tokens.push_back(inputToken);
                break;
            
            case ',':
                inputToken.type = COMMA;
                inputToken.character = ",";
                tokens.push_back(inputToken);
                break;

            case '=':
                if (nextChar == '=') {
                    inputToken.type = BOOLEAN_EQUAL;
                    inputToken.character = "==";
                    tokens.push_back(inputToken);
                    i++;
                } else {
                    inputToken.type = ASSIGNMENT;
                    inputToken.character = "=";
                    tokens.push_back(inputToken);
                }
                
                break;

            case '+':
                inputToken.type = PLUS;
                inputToken.character = "+";
                tokens.push_back(inputToken);
                break;

            case '-':
                if (std::isdigit(nextChar)) {
                    i++;
                    inputToken.type = INTEGER;
                    inputToken.character = '-';
                    while (std::isdigit(input[i])) {
                        inputToken.character += input[i++];
                    }

                    i--;
                    tokens.push_back(inputToken);
                } else {
                    inputToken.type = MINUS;
                    inputToken.character = "-";
                    tokens.push_back(inputToken);
                }
            
                break;

            case '/':
                inputToken.type = DIVIDE;
                inputToken.character = "/";
                tokens.push_back(inputToken);
                break;

            case '*':
                inputToken.type = ASTERISK;
                inputToken.character = "*";
                tokens.push_back(inputToken);
                break;

            case '%':
                inputToken.type = MODULO;
                inputToken.character = "%";
                tokens.push_back(inputToken);
                break;

            case '^':
                inputToken.type = CARAT;
                inputToken.character = "^";
                tokens.push_back(inputToken);
                break;
            
            case '<':
                if (nextChar == '=') {
                    inputToken.type = LT_EQUAL;
                    inputToken.character = "<=";
                    tokens.push_back(inputToken);
                    i++;
                } else {
                    inputToken.type = LT;
                    inputToken.character = "<";
                    tokens.push_back(inputToken);
                }
                
                break;
            
            case '>':
                if (nextChar == '=') {
                    inputToken.type = GT_EQUAL;
                    inputToken.character = ">=";
                    tokens.push_back(inputToken);
                    i++;
                } else {
                    inputToken.type = GT;
                    inputToken.character = ">";
                    tokens.push_back(inputToken);
                }

                break;

            case '&':
                if (nextChar == '&') {
                    inputToken.type = BOOLEAN_AND_OPERATOR;
                    inputToken.character = "&&";
                    tokens.push_back(inputToken);
                    i++;
                }
                
                break;

            case '|':
                if (nextChar == '|') {
                    inputToken.type = BOOLEAN_OR_OPERATOR;
                    inputToken.character = "||";
                    tokens.push_back(inputToken);
                    i++;
                }
                
                break;
            
            case '!':
                if (nextChar == '=') {
                    inputToken.type = BOOLEAN_NOT_EQUAL;
                    inputToken.character = "!=";
                    tokens.push_back(inputToken);
                    i++;
                } else {
                    inputToken.type = BOOLEAN_NOT_OPERATOR;
                    inputToken.character = "!";
                    tokens.push_back(inputToken);
                }

                break;

            default:
                if (std::isdigit(input[i])) {
                    while (!std::isspace(input[i]) && !(std::find( listOfSymbols.begin(), listOfSymbols.end(), input[i]) != listOfSymbols.end())) {
                        if (!isdigit(input[i])) {
                            std::cout << "Syntax error on line " << lineNumber << ": invalid integer\n";
                            exit(0);
                        }

                        inputToken.character += input[i++];
                    }

                    inputToken.type = INTEGER;
                    
                    
                } else {
                    while (!std::isspace(input[i]) && !(std::find( listOfSymbols.begin(), listOfSymbols.end(), input[i]) != listOfSymbols.end())) {
                        inputToken.character += input[i++];
                    }

                    inputToken.type = IDENTIFIER;
                }



                i--;
                tokens.push_back(inputToken);

                break;
        }
    }

    return tokens;
}


void displayTokens(const vector<Token>& tokens) {
    std::ofstream outputFile("results.txt");

    if (!outputFile) {
        std::cerr << "Couldn't open output file\n";
        exit(1);
    }

    outputFile << "Token list: " << endl << endl;
    for (const auto& token: tokens) {
        std::string tokenType = "Token type: ";
        std::string tokenString = "Token: ";
        switch (token.type) {
            case IDENTIFIER:
                tokenType += "IDENTIFIER";
                break;

            case INTEGER:
                tokenType += "INTEGER";
                break;

            case STRING:
                tokenType += "STRING";
                break;

            case LEFT_PARENTHESIS:
                tokenType += "LEFT_PARENTHESIS";
                break;

            case RIGHT_PARENTHESIS:
                tokenType += "RIGHT_PARENTHESIS";
                break;

            case LEFT_BRACKET:
                tokenType += "LEFT_BRACKET";
                break;

            case RIGHT_BRACKET:
                tokenType += "RIGHT_BRACKET";
                break;

            case LEFT_BRACE:
                tokenType += "LEFT_BRACE";
                break;

            case RIGHT_BRACE:
                tokenType += "RIGHT_BRACE";
                break;

            case DOUBLE_QUOTE:
                tokenType += "DOUBLE_QUOTE";
                break;

            case SINGLE_QUOTE:
                tokenType += "SINGLE_QUOTE";
                break;

            case SEMICOLON:
                tokenType += "SEMICOLON";
                break;

            case COMMA:
                tokenType += "COMMA";
                break;

            case ASSIGNMENT:
                tokenType += "ASSIGNMENT";
                break;

            case PLUS:
                tokenType += "PLUS";
                break;

            case MINUS:
                tokenType += "MINUS";
                break;

            case DIVIDE:
                tokenType += "DIVIDE";
                break;

            case ASTERISK:
                tokenType += "ASTERISK";
                break;

            case MODULO:
                tokenType += "MODULO";
                break;

            case CARAT:
                tokenType += "CARAT";
                break;

            case LT:
                tokenType += "LT";
                break;

            case GT:
                tokenType += "GT";
                break;

            case LT_EQUAL:
                tokenType += "LT_EQUAL";
                break;

            case GT_EQUAL:
                tokenType += "GT_EQUAL";
                break;
        
            case BOOLEAN_AND_OPERATOR:
                tokenType += "BOOLEAN_AND_OPERATOR";
                break;

            case BOOLEAN_OR_OPERATOR:
                tokenType += "BOOLEAN_OR_OPERATOR";
                break;

            case BOOLEAN_NOT_OPERATOR:
                tokenType += "BOOLEAN_NOT_OPERATOR";
                break;

            case BOOLEAN_EQUAL:
                tokenType += "BOOLEAN_EQUAL";
                break;

            case BOOLEAN_NOT_EQUAL:
                tokenType += "BOOLEAN_NOT_EQUAL";
                break;

            case BOOLEAN_TRUE:
                tokenType += "BOOLEAN_TRUE";
                break;

            case BOOLEAN_FALSE:
                tokenType += "BOOLEAN_FALSE";
                break;

        }

        tokenString += token.character;
        outputFile << tokenType << '\n' << tokenString << '\n' << '\n';
    }

    outputFile.close();
}




int main(int argc, char *argv[]) {

    
    if (argc != 2 ) {
        cerr << "Error! There is not a correct number of command line arguments.\n";
        return 1;
    }
    string filename = argv[1];
    ifstream inputFile(filename.c_str());

    if (!inputFile) {
        std::cerr << "Error. Unable to open the file :( \n"; // Error out if we are unable to open up the file
        return 1;
    }

//Create the suggested State
enum State {
    ANYTHING, 
    SLASH,
    ASTERICK,
    SINGLE_LINE_COMMENT, // A comment pertaining '//'
    MULTI_LINE_COMMENT, // A comment pertaining '/* bla */
    SINGLE_QUOTE,
    DOUBLE_QUOTE, 
    Error
};

    State state = ANYTHING;
    string result = "";
    int line = 1; 
    int mult_line = 0;
    char currentChar;

    while (inputFile.get(currentChar)) {

        switch (state) {

            //Handle Anything 
            case ANYTHING:
                if (currentChar == '/') {
                    state = SLASH;
                    char nextChar = inputFile.peek();
                    result += (nextChar == '/' || nextChar == '*') ? ' ' : currentChar;
                } else if (currentChar == '"') {
                    state = DOUBLE_QUOTE;
                    result += currentChar;
                } else if (currentChar == '\'') {
                    state = SINGLE_QUOTE;
                    result += currentChar;
                }else if (currentChar == '\n'){ //Check for new line
                    result += currentChar;
                    line += 1; 
                } else {
                    result += currentChar;
                }
                break;
            
            //Handle Slash
            case SLASH:
                if (currentChar == '/') {
                    state = SINGLE_LINE_COMMENT;
                    result += ' ';
                } else if (currentChar == '*') {
                    state = MULTI_LINE_COMMENT;
                    result += ' ';
                } else {
                    state = ANYTHING;
                    result += currentChar;
                }
                break;

            //Handle Star 
            case ASTERICK:
                if (currentChar == '/') {
                    state = ANYTHING;
                }else if (currentChar == '\n'){
                    line += 1; 
                    state = MULTI_LINE_COMMENT;
                } else if (currentChar != '*') {
                    state = MULTI_LINE_COMMENT;
                } 
                result += ' ';
                break;

            //Handle single line 
            case SINGLE_LINE_COMMENT:
                if (currentChar == '\n') {
                    line += 1; //Check for new line
                    state = ANYTHING;
                    result += currentChar;
                } else {
                    result += ' ';
                }
                break;

            //Handle Multiple Line 
            case MULTI_LINE_COMMENT:
                if (currentChar == '*') {
                    state = ASTERICK;
                    result += ' ';
                } else {
                    line  += currentChar == '\n' ? 1 : 0 ;  
                    result += currentChar == '\n' ? '\n' : ' ';
                    mult_line += currentChar == '\n' ? 1 : 0 ;
                    
                } 
                break;

            //Needs code to handle escape characters
            case SINGLE_QUOTE: 
                if (currentChar == '\'') {
                    state = ANYTHING;
                }
                result += currentChar;
                break;

            // Neds code to handle escape characters
            case DOUBLE_QUOTE:
                if (currentChar == '"') {
                    state = ANYTHING;
                } 
                result += currentChar;
                break;

            case Error:
                //cout << "ERROR: Program contains C-style, unterminated comment on line " << line << endl;
                break;
        }
    }
    if (state == Error){
         cout << "ERROR: Program contains C-style, unterminated comment on line " << line << endl;
 
    }else if(state == MULTI_LINE_COMMENT){
         cout << "ERROR: Program contains C-style, unterminated comment on line " << line - mult_line << endl;
    }
    inputFile.close(); // Close the file when we are done working.
    vector<Token> tokens = tokenize(result);
    displayTokens(tokens);
}


// For instructions on how to run, please see our read me file.
// This project has successfully run on Blue!