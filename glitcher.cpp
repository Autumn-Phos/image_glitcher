#include <iostream>
#include <complex>
#include <vector>

void apply_newton_fractal_glitch(std::vector<char>& data) 
{
    std::string colors_to_convert;
    std::cout << "какие цвета менять (R/G/B) формат ввода (YNY)\n";
    std::cin >> colors_to_convert;

    bool colors_to_convert_boolean[3] = {false, false, false};
    for (size_t i = 0; i < colors_to_convert.size(); i++)
    {
        colors_to_convert_boolean[i] = colors_to_convert[i] == 'Y' || colors_to_convert[i] == 'y'; 
    }

    size_t pixel_count = (data.size() - 54) / 3;
    size_t update_step = pixel_count / 100;
    if (update_step == 0) update_step = 1;

    const int bar_width = 80;

    for (size_t p = 0, i = 54; i + 2 < data.size(); ++p, i += 3)
    {
        char R = static_cast<char>(data[i + 2]);
        char G = static_cast<char>(data[i + 1]);
        char B = static_cast<char>(data[i]);

        std::complex<double> z(static_cast<double>(R) / 255.0, static_cast<double>(G) / 255.0);

        for (size_t j = 0; j < 5; ++j)
        {
            if (std::abs(z) < 1e-6) break;
            z = z - (std::pow(z, 3) - std::complex<double>(1, 0)) / (3.0 * std::pow(z, 2));
        }

        char R_new = static_cast<char>(std::abs(z.real()) * 255.0) % 256;
        char G_new = static_cast<char>(std::abs(z.imag()) * 255.0) % 256;
        char B_new = static_cast<char>(std::abs(std::abs(z)) * 255.0) % 256;

        if (colors_to_convert_boolean[0]) data[i + 2] = static_cast<char>(R_new);
        if (colors_to_convert_boolean[1]) data[i + 1] = static_cast<char>(G_new);
        if (colors_to_convert_boolean[2]) data[i] = static_cast<char>(B_new);

        if (p % update_step == 0 || p == pixel_count - 1)
        {
            double progress = static_cast<double>(p + 1) / pixel_count;
            int pos = static_cast<int>(bar_width * progress);

            std::cout << "\r[";
            for (int k = 0; k < bar_width; ++k) {
                if (k < pos) std::cout << "█";
                else if (k == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << "% " << std::flush;
        }
    }

    std::cout << "\n";
    if (std::cin.peek() == '\n') std::cin.get();
}

void invert_colors(std::vector<char>& data) 
{
    for (size_t i = 54; i < data.size(); i++)
    {
        data[i] ^= 0xFF;
    }
}

void delete_one_byte(std::vector<char>& data) 
{
    for (size_t i = 56; i < data.size(); i++)
    {
        data[i-1] = data[i];
    }
}