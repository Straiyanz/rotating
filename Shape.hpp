#ifndef _SHAPE_HPP_
#define _SHAPE_HPP_

#include <array>
#include <list>
#include <vector>

#include "Coord.hpp"

class Shape {
   protected:
    const std::array<char, 8> lum{".,-=+#@"};
    Coord<double> light{0, 1, 0};
    std::vector<Coord<double>> pos;
    std::vector<std::pair<Coord<double>, char>> proj;
    int z1;
    const int size;
    const int width{115}, height{30};  // canvas dimentions

   private:
    char get_repr(const Coord<double> &co);
    std::list<Coord<double>> get_nearby(const Coord<double> &co,
                                        const size_t n) const;

   public:
    Shape(int size) : z1(size), size(size) {}
    ~Shape() = default;
    // Getters:
    double get_z1() const { return z1; }
    int get_size() const { return size; }
    // Setters.
    void set_z1(double z1) { this->z1 = z1; }
    void set_proj();
    // Move shape along axis.
    void move_x(double x);
    void move_y(double y);
    void move_z(double z);
    // Rotations about an axis.
    void rotate_x(double theta);  // rotate in degrees
    void rotate_y(double theta);  // rotate in degrees
    void rotate_z(double theta);  // rotate in degrees
    // Display things.
    void display() const;
    void print_pos() const;
    void print_proj() const;
    // Not currently using these, thing for another day
    // std::vector<Coord> get_proj() const { return proj; }
    // void move_light(double x, double y, double z) { light = Coord{x, y, z}; }
    // void move_light(Coord<double> &co) { light = co; }
};

// void sleep(double ms);

#endif  // _SHAPE_HPP_