#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>

int utf8_length(const std::string& str) {
    int len = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = str[i];
        if ((c & 0b10000000) == 0) i += 1;
        else if ((c & 0b11100000) == 0b11000000) i += 2;
        else if ((c & 0b11110000) == 0b11100000) i += 3;
        else if ((c & 0b11111000) == 0b11110000) i += 4;
        else i += 1; // fallback
        ++len;
    }
    return len;
}

int drawMenu() {
    std::vector<std::string> main_options = {
        "Glitch with newton fractal                 ║\n",
        "Invert image colors                        ║\n",
        "Delete one byte                            ║\n",
        "Change image                               ║\n",
        "Exit                                       ║\n"
    };

    std::vector<std::string> options_for_fractal = {
        "Glitch with newton                         ║\n",
        "Sierpiński triangle                        ║\n",
        "Koch snowflake                             ║\n",
        "Back                                       ║\n"
    };

    int selected = 0;

    while (true) {
        system("cls");
        std::cout << R"(
╔══════════════════════════════════════════════╗
║               IMAGE GLITCHER                 ║
╠══════════════════════════════════════════════╣
)";
        for (size_t i = 0; i < main_options.size(); ++i) {
            std::cout << "║ ";
            if (i == selected)
                std::cout << "> ";
            else
                std::cout << "  ";
            std::cout << main_options[i];
            int pad = 42 - utf8_length(main_options[i]);
            std::cout << std::string(std::max(0, pad), ' ');
        }
        std::cout << "╚══════════════════════════════════════════════╝\n";

        int key = _getch();
        if (key == 224 || key == 0) {
            key = _getch();
            if (key == 72 && selected > 0)
                selected--;
            else if (key == 80 && selected < main_options.size() - 1)
                selected++;
        } else if (key == 13) {
            return selected;
        }
    }
}