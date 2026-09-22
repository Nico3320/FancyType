#include <iostream>
#include <vector>
#include <unordered_map>

/* =========== TODO ===========
- Bordered Text muss mit Umbruch funktionieren
    -> for loop durch den Text bis er '\n' entdeckt, dann wissen wir ob und wo ein Umbruch ist. Dann muss man den Text splitten an den Umbruch stellen.
    -> vielleicht eine TEXT klasse? Dann kann man Farben an custom stellen setzen. Umbrüche etc.

*/

std::string char_to_string(char c) {
    std::string str;
    str.push_back(c);
    return str;
}

bool contains_line_break(std::string str) {
    for(char c : str) if(c == '\n') return true;
    return false;
}

std::unordered_map<std::string, std::string> COLORS = {
    {"BLACK", "\033[30m"},
    {"RED", "\033[31m"},
    {"GREEN", "\033[32m"},
    {"YELLOW", "\033[33m"},
    {"BLUE", "\033[34m"},
    {"MAGENTA", "\033[35m"},
    {"CYAN", "\033[36m"},
    {"WHITE", "\033[37m"},

    {"BRIGHT_BLACK", "\033[90m"},
    {"BRIGHT_RED", "\033[91m"},
    {"BRIGHT_GREEN", "\033[92m"},
    {"BRIGHT_YELLOW", "\033[93m"},
    {"BRIGHT_BLUE", "\033[94m"},
    {"BRIGHT_MAGENTA", "\033[95m"},
    {"BRIGHT_CYAN", "\033[96m"},
    {"BRIGHT_WHITE", "\033[97m"},

    {"RESET", "\033[0m"},

    {"BOLD", "\033[1m"},
    {"DIM", "\033[2m"},
    {"ITALIC", "\033[3m"},
    {"UNDERLINE", "\033[4m"},
    {"BLINK", "\033[5m"},
    {"REVERSE", "\033[7m"},
    {"HIDDEN", "\033[8m"},
    {"STRIKETHROUGH", "\033[9m"},

    {"BG_BLACK", "\033[40m"},
    {"BG_RED", "\033[41m"},
    {"BG_GREEN", "\033[42m"},
    {"BG_YELLOW", "\033[43m"},
    {"BG_BLUE", "\033[44m"},
    {"BG_MAGENTA", "\033[45m"},
    {"BG_CYAN", "\033[46m"},
    {"BG_WHITE", "\033[47m"},

    {"BG_BRIGHT_BLACK", "\033[100m"},
    {"BG_BRIGHT_RED", "\033[101m"},
    {"BG_BRIGHT_GREEN", "\033[102m"},
    {"BG_BRIGHT_YELLOW", "\033[103m"},
    {"BG_BRIGHT_BLUE", "\033[104m"},
    {"BG_BRIGHT_MAGENTA", "\033[105m"},
    {"BG_BRIGHT_CYAN", "\033[106m"},
    {"BG_BRIGHT_WHITE", "\033[107m"}
};

class COLOR {
    public:
    int r = 255;
    int g = 255;
    int b = 255;

    COLOR() {}
    COLOR(int pR, int pG, int pB) {
        r = pR;
        g = pG;
        b = pB;
    }
};

class TEXT {
    private:
    std::string raw_input;
    std::vector<std::string> vec;

    public:
    TEXT(std::string str) {
        raw_input = str;
        if(contains_line_break(str)) {
            vec = split_on(str, '\n');
        }
    }
    std::vector<std::string> split_on(std::string str, char c) {
        std::vector<std::string> res;
        std::string current;
        for(char ch : str) {
            if(ch == c) {
                res.push_back(current);
                current = "";
            } else current.push_back(ch);
        }
        return res;
    }
};

std::string color_code(int r, int g, int b) {
    std::string res = "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    return res;
}
std::string color_code(COLOR color) {
    std::string res = "\033[38;2;" + std::to_string(color.r) + ";" + std::to_string(color.g) + ";" + std::to_string(color.b) + "m";
    return res;
}

class BORDER {
    public:
    char top    = '%';
    char bottom = '%';
    char left   = '%';
    char right  = '%';
    char corner = '%';
    bool strike =   1;
    bool bold   =   1;
    COLOR color = COLOR(255,255,255);

    public:
    BORDER() {}
    BORDER(char pTop, char pBottom, char pLeft, char pRight, char pCorner, bool pStrike, bool pBold, COLOR pColor) {
        top    = pTop;
        bottom = pBottom;
        left   = pLeft;
        right  = pRight;
        corner = pCorner;
        strike = pStrike;
        bold   = pBold;
        color  = pColor;
    }
    BORDER(std::vector<char> TBLRC, bool pStrike, bool pBold, COLOR pColor) {
        top    = TBLRC[0];
        bottom = TBLRC[1];
        left   = TBLRC[2];
        right  = TBLRC[3];
        corner = TBLRC[4];
        strike = pStrike;
        bold   = pBold;
        color  = pColor;
    }
    BORDER(std::vector<char> TBLRC) {
        top    = TBLRC[0];
        bottom = TBLRC[1];
        left   = TBLRC[2];
        right  = TBLRC[3];
        corner = TBLRC[4];
    }
};

void mod(std::vector<std::string> mods) {
    for(std::string str : mods) std::cout << str;
}

void line(int size, COLOR color, std::string pieces) {
    std::cout << color_code(color.r, color.g, color.b);
    for(int i = 0; i < size; i++) std::cout << pieces;
    std::cout << COLORS["RESET"];
}
void line(int size, std::string pieces) {
    for(int i = 0; i < size; i++) std::cout << pieces;
    std::cout << COLORS["RESET"];
}

void bordered_text(std::string text, BORDER border, int padding) {
    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);

    std::cout << border.corner;
    line(text.size()+(padding*2)+(padding*2), char_to_string(border.top));
    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);

    std::cout << char_to_string(border.right) << "\n";
    for(int i = 0; i < padding; i++) {
        std::cout << char_to_string(border.left);
        std::cout << COLORS["RESET"];
        line(text.size()+(padding*2)+(padding*2), " ");

        if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
        if(border.bold)   std::cout << COLORS["BOLD"];
        std::cout << color_code(border.color);
        std::cout << char_to_string(border.right);
        std::cout << "\n";
    }
    std::cout << char_to_string(border.left);
    std::cout << COLORS["RESET"];
    for(int i = 0; i < padding*2; i++) std::cout << " ";
    std::cout << text;
    for(int i = 0; i < padding*2; i++) std::cout << " ";

    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);
    std::cout << char_to_string(border.right) << "\n";
    for(int i = 0; i < padding; i++) {
        std::cout << char_to_string(border.left);
        std::cout << COLORS["RESET"];
        line(text.size()+(padding*2)+(padding*2), " ");

        if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
        if(border.bold)   std::cout << COLORS["BOLD"];
        std::cout << color_code(border.color);
        std::cout << char_to_string(border.right);
        std::cout << "\n";
    }
    std::cout << border.corner;

    line(text.size()+(padding*2)+(padding*2), char_to_string(border.top));
    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);

    std::cout << char_to_string(border.right);
}
void bordered_text(std::string text, BORDER border, int paddingVertical, int paddingHorizontal) {
    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);

    std::cout << border.corner;
    line(text.size()+(paddingHorizontal*2), char_to_string(border.top));
    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);

    std::cout << char_to_string(border.right) << "\n";
    for(int i = 0; i < paddingVertical; i++) {
        std::cout << char_to_string(border.left);
        std::cout << COLORS["RESET"];
        line(text.size()+(paddingHorizontal*2), " ");

        if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
        if(border.bold)   std::cout << COLORS["BOLD"];
        std::cout << color_code(border.color);
        std::cout << char_to_string(border.right);
        std::cout << "\n";
    }
    std::cout << char_to_string(border.left);
    std::cout << COLORS["RESET"];
    for(int i = 0; i < paddingHorizontal; i++) std::cout << " ";
    std::cout << text;
    for(int i = 0; i < paddingHorizontal; i++) std::cout << " ";

    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);
    std::cout << char_to_string(border.right) << "\n";
    for(int i = 0; i < paddingVertical; i++) {
        std::cout << char_to_string(border.left);
        std::cout << COLORS["RESET"];
        line(text.size()+(paddingHorizontal*2), " ");

        if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
        if(border.bold)   std::cout << COLORS["BOLD"];
        std::cout << color_code(border.color);
        std::cout << char_to_string(border.right);
        std::cout << "\n";
    }
    std::cout << border.corner;

    line(text.size()+(paddingHorizontal*2), char_to_string(border.top));
    if(border.strike) std::cout << COLORS["STRIKETHROUGH"];
    if(border.bold)   std::cout << COLORS["BOLD"];
    std::cout << color_code(border.color);

    std::cout << char_to_string(border.right);
}

int main() {
    
}