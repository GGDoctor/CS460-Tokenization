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



//struct Token
//Store store token information
struct Token {
    TokenType type;
    string character;
};



//This needs a ton of work 


vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    string currentToken; //Read char by char
    bool inComment = false;
    bool inString = false;

    for (size_t i=0;i < input.size(); ++i) {
        Token inputToken;
        switch(input[i]){
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
                inputToken.character = "[]";
                tokens.push_back(inputToken);
                break;

            case ']':
                inputToken.type = RIGHT_BRACKET;
                inputToken.character = "]";
                tokens.push_back(inputToken);
                break;

            case '{':
                inputToken.type = LEFT_BRACKET;
                inputToken.character = "{";
                tokens.push_back(inputToken);
                break;

            case '}':
                inputToken.type = RIGHT_BRACKET;
                inputToken.character = "}";
                tokens.push_back(inputToken);
                break;

            case '"':
                inputToken.type = DOUBLE_QUOTE;
                inputToken.character = "\"";
                tokens.push_back(inputToken);
                break;

            case '\'':
                inputToken.type = SINGLE_QUOTE;
                inputToken.character = "\'";
                tokens.push_back(inputToken);
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
                inputToken.type = ASSIGNMENT;
                inputToken.character = "=";
                tokens.push_back(inputToken);
                break;

            case '+':
                inputToken.type = PLUS;
                inputToken.character = "+";
                tokens.push_back(inputToken);
                break;

            case '-':
                inputToken.type = MINUS;
                inputToken.character = "-";
                tokens.push_back(inputToken);
                break;

            case '\\':
                inputToken.type = DIVIDE;
                inputToken.character = "\\";
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
                inputToken.type = LT;
                inputToken.character = "<";
                tokens.push_back(inputToken);
                break;
            
            case '>':
                inputToken.type = GT;
                inputToken.character = ">";
                tokens.push_back(inputToken);
                break;
            
            case '<=':
                inputToken.type = LT_EQUAL;
                inputToken.character = "<=";
                tokens.push_back(inputToken);
                break;

            case '>=':
                inputToken.type = GT_EQUAL;
                inputToken.character = ">=";
                tokens.push_back(inputToken);
                break;

            case '&':
                inputToken.type = BOOLEAN_AND_OPERATOR;
                inputToken.character = "&";
                tokens.push_back(inputToken);
                break;

            case '|':
                inputToken.type = BOOLEAN_OR_OPERATOR;
                inputToken.character = "|";
                tokens.push_back(inputToken);
                break;
            
            case '!':
                inputToken.type = BOOLEAN_NOT_OPERATOR;
                inputToken.character = "!";
                tokens.push_back(inputToken);
                break;
        }
    }
}


void displayTokens(const vector<Token>& tokens) {
    cout << "Token list: " << endl << endl;
    for (const auto& token: tokens) {
        cout << "Token type: ";
        switch (token.type) {

            case LEFT_PARENTHESIS:
            cout << "LEFT_PARENTHESIS";
            break;




        }
    }
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
                }else if (currentChar == '*'){  //Check if  */ appears before  /* 
                    char nextChar = inputFile.peek();
                    state = (nextChar == '/') ? Error : ANYTHING;
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

            // needs code to handle escape characters
            case SINGLE_QUOTE: 
                if (currentChar == '\'') {
                    state = ANYTHING;
                }
                result += currentChar;
                break;

            // needs code to handle escape characters
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
    // else{
    //     cout << result; 
    // }
    inputFile.close(); // Close the file when we are done working.
    tokenize(result);
    // return 0;
}


//I downloaded the file and put them into the project
//then did a g++ -o Tokenization Tokenization.cpp
//then did ./Tokenization programming_assignment_2-test_file_2.c
//this worked.