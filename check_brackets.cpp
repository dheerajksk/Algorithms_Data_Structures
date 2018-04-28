#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

void showstack(std::stack <Bracket> stacktoprint){
    while(!stacktoprint.empty()){
    Bracket temp(stacktoprint.top());
    std::cout << temp.type << '\t';
    stacktoprint.pop();
    }
    std::cout << '\n';
    }

int main() {
    std::string text;
    getline(std::cin, text);

    int curr_position=0;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            Bracket temp(next, position);
            // Process opening bracket, write your code here
            opening_brackets_stack.push(temp);
            curr_position = position + 1;
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
            if(opening_brackets_stack.empty()) { //std::cout << "empty: " << opening_brackets_stack.empty() << "\n"; 
                curr_position = position + 1; 
                break;
                }
            else {
              Bracket topofstack(opening_brackets_stack.top());
              opening_brackets_stack.pop();
              if( (topofstack.type == '(' && next != ')') || (topofstack.type == '[' && next != ']') || (topofstack.type == '{' && next != '}')){
                  curr_position = position + 1;
                  break;
                  }
              else{
                  //std::cout << "Match! on stack: " << topofstack.type << " next: " << next << std::endl;
                  curr_position = - 1;
                  }
              }
        }
    }

    
    if( curr_position > 0) std::cout << curr_position << std::endl;
    else if(!opening_brackets_stack.empty()) {
        Bracket topofstack(opening_brackets_stack.top());
        std::cout << topofstack.position + 1 << std::endl;
        }
    else std::cout << "Success";

    // Printing answer, write your code here
    
    //showstack(opening_brackets_stack);

    return 0;
}
