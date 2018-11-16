#include "Cursor.cpp"

int main() {
    const std::string COMMAND_LIST = " l - to move the cursor left \n r - to move the cursor right \n d - to delete the next character \n "
                                     "d# - where # is an integer, to delete the next # characters \n b - to delete the previous character \n "
                                     "b# where # is an integer, to delete the previous # character \n "
                                     "i c - to insert the character c at the current position \n h - to return the cursor to the home position \n "
                                     "e - to move the cursor to the end position \n u - to undo the last non-undo command entered \n "
                                     "? - to display this list \n $ - to end program execution \n";
    Cursor<char>ourCursor;

    std::cout << "Welcome!"<< std::endl;
    std::cout << "To begin editing your text, use one of the following commands:" <<std::endl;
    std::cout << COMMAND_LIST;
    while(true){// run until user exits
        char cmd = std::cin.get();
        if(cmd == 'i'){
            ourCursor.insert(std::cin.ignore(255,' ').get());
        }else if(cmd == '?'){
            std::cout << COMMAND_LIST;
        }else if(cmd == 'l'){
            ourCursor.left();
        }else if(cmd == 'r'){
            ourCursor.right();
        }else if(cmd == 'd'){
            if(std::cin.peek() == '\n'){
                ourCursor.del();
            } else{
                ourCursor.del((std::cin.get() - '0'));
            }
        }else if(cmd == 'b'){
            if(std::cin.peek() == '\n'){
                ourCursor.back();
            } else{
                ourCursor.back(std::cin.get() - '0');
            }
        }else if(cmd == 'h'){
            ourCursor.home();
        }else if(cmd == 'e'){
            ourCursor.end();
        }else if(cmd == 'u'){
            if(std::cin.peek() == '\n'){
                ourCursor.undo();
            } else{
                ourCursor.undo(std::cin.get() - '0');
            }
        }else if(cmd == '$'){
            std::cout << "Goodbye!";
            break;
        }else{
            std::cout << "Invalid input, please try again." << std::endl;
        }
        std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');//flush input stream
    }

    return 0;
}