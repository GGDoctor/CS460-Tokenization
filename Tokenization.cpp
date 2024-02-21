// Ignore comments
// The objective of this project is to take the first step torwards building an interpreter, ignoring comments
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
    LEFT_BRACE,
    RIGHT_BRACE,
    ASSIGNMENT,
    COMMA,
    SEMICOLON,
    DOUBLE_QUOTE,
    INVAlID_INTEGER
};


//struct Token
//Store store token information
struct Token {
    TokenType type;
    string lexan;
}


vector<Token> tokenize(const string& input) {
    
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
    else{
        cout << result; 
    }
    inputFile.close(); // Close the file when we are done working.
    //std::cout << result;

    return 0;
}


//I downloaded the file and put them into the project
//then did a g++ -o IgnoreComments IgnoreComments.cpp
//then did ./IgnoreComments programming_assignment_1-test_file_2.c
//this worked.