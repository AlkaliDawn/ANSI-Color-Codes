#include <windows.h>
#include <cctype>

// HEX TO ANSI COLOR //
void remove_hashtag_from_string(std::string &i, int j) {
    
    std::string k; // temp variable
    
    if (i.find_first_of("#") != std::string::npos) { // If hexadecimal has hashtag at beginning, remove it by shifting elements 1 index left
        
        
        i.resize(i.size()-1);
    }
}
void make_string_lowercase(std::string &c, std::string &i, int a) {
    if (c.find_first_not_of("ABCDEF") == std::string::npos) { // If character is uppercase, make lowercase
        i[a] = tolower(i[a]);
        c = i[a];
    }
}

std::string COLOR(std::string i, bool foreground, bool bold, bool underline) {
    std::string x, c; int b; int e[3]{};
    if (foreground) { x = "\033[0m\033[38;2;"; } else { x = "\033[0m\033[48;2;"; }
    remove_hashtag_from_string(i, i.size());
    for (int a = 0; a < 6; a++) {
        c = i[a];
        if (c.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos) { // Make sure current character is hexadecimal
            make_string_lowercase(c, i, a);
            if (a % 2 == 0) { // a is even, use 16^1 (16)
                b = 0;
                if (c.find_first_not_of("abcdef") ==
                    std::string::npos) { // If character is alphabetical, convert to decimal
                    b = b + (((int) i[a] - 87) * 16);
                }
                if (c.find_first_not_of("0123456789") ==
                    std::string::npos) { // numerical character, subtract 48 for conversion
                    b = b + (((int) i[a] - 48) * 16);
                }
                
            } else { // a is odd, use 16^0 (1)
                if (c.find_first_not_of("abcdef") ==
                    std::string::npos) { // If character is alphabetical, convert to decimal
                    b = b + ((int) i[a] - 87);
                }
                if (c.find_first_not_of("0123456789") ==
                    std::string::npos) { // numerical character, subtract 48 for conversion
                    b = b + ((int) i[a] - 48);
                }
                switch (a) {
                    case 1:
                        e[0] = b;
                        break;
                    case 3:
                        e[1] = b;
                        break;
                    case 5:
                        e[2] = b;
                }
                for (char d: std::to_string(b)) {
                    x.push_back(d);
                }
                if (a != 5) x.push_back(';'); else x.push_back('m');
            }
        }
    }
    if (bold) { x += "\033[1m"; }
    if (underline) { x += ("\033[58;2;" + std::to_string(e[0]) + ";"); }
    return x;
}