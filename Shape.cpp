#include "Shape.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numbers>
#include <string>

void Shape::move_x(double x) {
    for (auto &co : pos) co.set_x(co.get_x() + x);
}

void Shape::move_y(double y) {
    for (auto &co : pos) co.set_y(co.get_y() + y);
}

void Shape::move_z(double z) {
    for (auto &co : pos) co.set_z(co.get_z() + z);
}

void Shape::set_proj() {
    calculate_normals();
    proj.clear();
    for (auto &co : pos) {
        if (!co.get_z() == 0) {                    // dodge / 0 errors
            int x1{co.get_x() * z1 / co.get_z()};  // type:ignore
            int y1{co.get_y() * z1 / co.get_z()};  // type:ignore
            Coord<int> temp{x1, y1};
            if (std::find(proj.begin(), proj.end(),
                          temp) == proj.end()) {  // z filter.
                // if we don't find a match, add the point
                proj.push_back(temp);
            }
        }
    }
}

void Shape::calculate_normals() const {
    for (size_t i{}; i < pos.size(); i++) {
        if (i == 0) {
            // wrap to end
        } else if (i == (pos.size() - 1)) {
            // wrap to front
        } else {
            auto A = pos.at(i);
            auto B = pos.at(i-1);
            auto C = pos.at(i+1);
            // Coord<int> normal = Coord<int>::cross((B-A), (C-A));
            // std::cout << normal;
        }
        std::cout << std::endl;
    }
}

void Shape::display() const {
    std::string ss{};
    // printf("\x1b[H");  // Move cursor to the top-left corner ("Home")
    for (int y{-15}; y <= 15; y++) {
        for (int x{-size * 2}; x <= size * 2; x++) {
            if (std::find(pos.begin(), pos.end(), Coord<int>{x, y}) !=
                pos.end()) {
                ss += "#";
            } else {
                ss += ".";
            }
        }
        ss += "\n";
    }
    std::cout << ss;
}

void Shape::print_pos() const {
    std::cout << "Current positions:" << std::endl;
    int counter{1};
    for (auto &co : pos) {
        std::cout << co << " ";
        if (counter++ % size == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Shape::print_proj() const {
    std::cout << "Projection into 2d:" << std::endl;
    int counter{1};
    for (auto &co : proj) {
        std::cout << co << " ";
        if (counter++ % size == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

double to_rad(double theta) { return theta * std::numbers::pi / 180; }

void Shape::rotate_x(double theta) {
    theta = to_rad(theta);
    const double sin_t = std::sin(theta);
    const double cos_t = std::cos(theta);

    for (auto &co : pos) {
        // x = x
        double y;
        double z;
        // x = x
        y = co.get_y() * cos_t + co.get_z() * sin_t;
        z = co.get_y() * -sin_t + co.get_z() * cos_t;
        // x = x
        co.set_y(round(y));
        co.set_z(round(z));
    }
    set_proj();
}

void Shape::rotate_y(double theta) {
    theta = to_rad(theta);
    const double sin_t = sin(theta);
    const double cos_t = cos(theta);

    for (auto &co : pos) {
        double x;
        // y = y
        double z;
        x = co.get_x() * cos_t + co.get_z() * -sin_t;
        // y = y
        z = co.get_x() * sin_t + co.get_z() * sin_t;
        co.set_x(round(x));
        // y = y
        co.set_z(round(z));
    }
    set_proj();
}

void Shape::rotate_z(double theta) {
    theta = to_rad(theta);
    const double sin_t = sin(theta);
    const double cos_t = cos(theta);

    for (auto &co : pos) {
        double x;
        double y;
        // z = z
        x = co.get_x() * cos_t + co.get_y() * -sin_t;
        y = co.get_x() * sin_t + co.get_y() * sin_t;
        // z = z
        co.set_x(round(x));
        co.set_y(round(y));
        // z = z
    }
    set_proj();
}
