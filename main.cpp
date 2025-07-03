#include <fstream>
#include <iostream>
#include <limits>
#include <Windows.h>
#include "glitcher.cpp"
#include "menu_renderer.cpp"

std::string const BASE_IMAGE_DIR_NAME = "images/";
std::string const FILE_FORMAT = ".bmp";

std::vector<char> read_bmp_file()
{
    std::string file_name;
    std::cout << "Write name of bmp file\n";
    std::cin >> file_name;

    std::string line;

    std::ifstream file(BASE_IMAGE_DIR_NAME + file_name + FILE_FORMAT, std::ifstream::binary);

    if (!file)
    {
        std::cerr << "✖️ File '" << file_name << ".bmp' not found or cannot be opened.\n";
        return {};
    }

    std::vector<char> data((std::istreambuf_iterator<char>(file)), {});

    if (data.size() < 54) {
        std::cerr << "✖️ File is too small to be a valid BMP.\n";
        return {};
    }

    file.close();
    std::cout << "✓ Successfully loaded '" << file_name << ".bmp' (" << data.size() << " bytes)\n";
    return data;
}

int main() 
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::cout << "✓ The console is set to UTF-8\n";

    std::vector<char> data = read_bmp_file();
    
    bool exit = true;

    if (std::cin.peek() == '\n') std::cin.get();

    while(exit)
    {
        int choice = drawMenu();
        
        switch (choice)
        {
        case 0:
            apply_newton_fractal_glitch(data);
            break;
        case 1:
            invert_colors(data);
            break;
        case 2:
            delete_one_byte(data);
            break;
        case 3:
            data = read_bmp_file();
            break;
        default:
            exit = false;
            continue;
        }
        
        std::string glitched_bmp_file_name;
        std::cout << "Write name for glitched bmp file (base name glitched)\n";
        std::getline(std::cin, glitched_bmp_file_name);

        glitched_bmp_file_name = BASE_IMAGE_DIR_NAME + (glitched_bmp_file_name == "" ? "glitched" : glitched_bmp_file_name) + FILE_FORMAT;

        std::ofstream out(glitched_bmp_file_name, std::ios::binary);
        out.write(reinterpret_cast<char*>(data.data()), data.size());
        out.close();

        std::cout << "Trying to open bmp file...\n";
        system(("start " + glitched_bmp_file_name).c_str());

        std::cout << "Press Enter to continue...\n";
        std::cin.get();
    }

    return 0;   
}