#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


struct Color {
    int r{};
    int g{};
    int b{};
};

int main() {
    std::ifstream img;
    img.open("input.ppm");

    if (!img.is_open()) {
        return 1;
    }

    auto get_num = [&]() -> int {
        std::stringstream ss;
        std::string c;
        img >> c;
        return std::stoi(c);
    };

    // skip word (P3)
    std::string c;
    img >> c;

    int n_cols = get_num();
    int n_rows_total = get_num();
    int max_color = get_num();
    int n_rows = n_cols;

    std::vector<std::vector<Color>> result(n_rows);
    for (auto &c : result) {
        c.resize(n_cols);
    }

    int cur_rows = 0;
    while (cur_rows < n_rows_total) {
        for (int row = 0; row < n_rows; row++) {
            auto &res_col = result[row];
            for (int col = 0; col < n_cols; col++) {
                Color pix{get_num(), get_num(), get_num()};
                auto &res = res_col[col];
                res.r = res.r / 2 + pix.r / 2;
                res.g = res.g / 2 + pix.g / 2;
                res.b = res.b / 2 + pix.b / 2;
            }
        }
        cur_rows += n_rows;
    }
    img.close();

    // Save result
    std::ofstream img_out;
    img_out.open("output.ppm", std::ios::out);
    img_out << "P3\n";
    img_out << std::to_string(n_cols) << " ";
    img_out << std::to_string(n_rows) << " ";
    img_out << std::to_string(max_color) << "\n";
    for (int row = 0; row < n_rows; row++) {
        auto &res_row = result[row];
        for (int col = 0; col < n_cols; col++) {
            auto &res = res_row[col];
            img_out << std::to_string(res.r) << " ";
            img_out << std::to_string(res.g) << " ";
            img_out << std::to_string(res.b) << " ";
        }
    }
    img_out.close();
    return 0;
}
