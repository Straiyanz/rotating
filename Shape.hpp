#ifndef _SHAPE_HPP_
#define _SHAPE_HPP_

#include <vector>

#include "Coord.hpp"

class Shape {
   protected:
    const char lum[8]{".,-=+#@"};
    std::vector<Coord<int>> pos;
    std::vector<Coord<int>> proj;
    // Coord<int> light{0, 300, 300};
    int z1;
    const int size;

   private:
    void set_proj();
    void calculate_normals() const;

   public:
    Shape(double z1, int size) : z1(z1), size(size) {}
    ~Shape() = default;
    // Getters:
    double get_z1() const { return z1; }
    int get_size() const { return size; }
    // Setters.
    void set_z1(double z1) { this->z1 = z1; }
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
    // void move_light(Coord<int> &co) { light = co; }
};

#endif  // _SHAPE_HPP_