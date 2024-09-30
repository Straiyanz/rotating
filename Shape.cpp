#include "Shape.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numbers>
#include <string>

// Helper functions
double to_rad(double theta) { return theta * std::numbers::pi / 180; }
double to_deg(double rad) { return rad * 180 / std::numbers::pi; }

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
    std::sort(pos.begin(), pos.end());  // Sort in ascending order
    proj.clear();                       // Clear projection vector
    for (auto &co : pos) {              // Don't display z > 0
        // double x1{co.get_x() * z1 / co.get_z()};
        // double y1{co.get_y() * z1 / co.get_z()};
        const Coord<double> temp{co.get_x(), co.get_y()};  // Create 2D Coord
        auto p = std::make_pair(temp, get_repr(co));
        // Z-filter: If we don't find a match, add the point.
        if (std::find_if(proj.begin(), proj.end(), [&temp](const auto &p) {
                return p.first == temp;
            }) == proj.end()) {
            proj.push_back(p);
        }
    }
}

char Shape::get_repr(const Coord<double> &co) {
    // Calculate normal
    auto near{get_nearby(co, 2)};
    auto B = near.front();
    auto C = near.back();
    auto normal{co.get_normal(B, C)};
    // Check if inside or outside of cube, if close to something then we need to
    // If the normal
    if (is_inside((normal * size))) {
        // std::cout << "We were inside!" << std::endl;
        normal = co.get_normal(C, B);
    }
    // std::cout << "Normal for: " << co << " : " << normal << std::endl;
    // Calculate angle of normal with light
    // double theta = acos((light * normal) /
    //                     (normal.get_magnitude() * light.get_magnitude()));
    // Using cross prod formula
    double theta = asin((light.cross(normal)).get_magnitude() /
                        (light.get_magnitude() * normal.get_magnitude()));
    // std::cout << theta << std::endl;
    if (std::isnan(theta)) {
        return 'n';  // this is bad if we see n's!
    }
    // Decide corresponding char
    double bin_size = std::numbers::pi / (lum.size() - 1);
    int index{static_cast<int>(std::floor(theta / bin_size))};
    // std::cout << lum[index] << std::endl;
    return lum[index];
    // return '.';
}

bool Shape::is_inside(const Coord<double> &co) const {
    int size = this->get_size();
    auto it = std::find_if(
        pos.begin(), pos.end(),
        [&co, size](const Coord<double> &c) { return co.dist(c) <= size / 2; });
    if (it != pos.end()) {
        return true;
    }
    return false;
}

// Return the closest n coords in list form.
std::list<Coord<double>> Shape::get_nearby(const Coord<double> &co,
                                           const size_t n) const {
    std::vector<Coord<double>> pos_sorted{pos};  // copy vector
    std::sort(pos_sorted.begin(), pos_sorted.end(),
              [&co](const auto &pos_co1, const auto &pos_co2) {
                  return co.dist(pos_co1) < co.dist(pos_co2);
              });  // sort by distance from the point
    std::list<Coord<double>> result;
    // Take first n many, not including the point itself.

    size_t index{1};
    Coord<double> temp;
    while (result.size() < n) {
        if (index != 1) {
            temp = pos_sorted.at(index);
            if (result.front().cross(pos_sorted.at(index)) !=
                Coord{0.0, 0.0, 0.0}) {
                result.push_back(pos_sorted.at(index));
            }
        } else {
            result.push_back(pos_sorted.at(index));
        }
        index++;
    }
    // Debugging
    // std::cout << "Closest coords to " << co << ": ";
    // for (const auto &c : result) std::cout << c << co.dist(c) << " ";
    // std::cout << std::endl;
    return result;
}

void Shape::display() const {
    std::string ss{};
    // printf("\x1b[2J");  // Clears the screen?
    for (int y{-height / 2}; y < height / 2; y++) {
        for (int x{-width / 2}; x < width / 2; x++) {
            // narrow by y
            Coord<double> point{static_cast<double>(x), static_cast<double>(y)};
            auto p = std::find_if(
                proj.begin(), proj.end(),
                [&point](const auto &p) { return point.dist(p.first) < 0.75; });
            if (p != proj.end()) {
                ss += (*p).second;
                // ss += (*p).second;
            } else {
                ss += " ";
            }
        }
        ss += "\n";
    }
    std::cout << ss;
    // printf("\x1b[H");   // Move cursor to the top-left corner ("Home")
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
    for (auto &pa : proj) {
        std::cout << "(" << pa.first << " " << pa.second << ") ";
        if (counter++ % size == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Shape::rotate_x(double theta) {
    theta = to_rad(theta);
    const double sin_t = std::sin(theta);
    const double cos_t = std::cos(theta);

    double old_y;
    for (auto &co : pos) {
        old_y = co.get_y();
        co.set_y(old_y * cos_t - co.get_z() * sin_t);
        co.set_z(old_y * sin_t + co.get_z() * cos_t);
    }
}

void Shape::rotate_y(double theta) {
    theta = to_rad(theta);
    const double sin_t = std::sin(theta);
    const double cos_t = std::cos(theta);

    double old_x;
    for (auto &co : pos) {
        old_x = co.get_x();
        co.set_x(old_x * cos_t + co.get_z() * sin_t);
        co.set_z(-old_x * sin_t + co.get_z() * cos_t);
    }
}

void Shape::rotate_z(double theta) {
    theta = to_rad(theta);
    const double sin_t = std::sin(theta);
    const double cos_t = std::cos(theta);

    double old_x;
    for (auto &co : pos) {
        old_x = co.get_x();
        co.set_x(old_x * cos_t - co.get_y() * sin_t);
        co.set_y(old_x * sin_t + co.get_y() * cos_t);
    }
}
