#ifndef _COORD_CPP_
#define _COORD_CPP_
#include <iostream>

/// @brief Coordinate system, with x, y, z points.
/// @tparam T: Must be numerical type.
template <typename T>
class Coord {
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Coord<U> co);

   private:
    T x, y, z;

   public:
    Coord(T x, T y, T z) : x(x), y(y), z(z) {}
    Coord(T x, T y) : Coord<T>(x, y, 0) {}  // for 2d stuffs
    Coord() : Coord<T>(0, 0, 0) {}
    // Coord(Coord<T> &&co) noexcept;          // Move constructor
    Coord(const Coord<T> &co)
        : Coord{co.get_x(), co.get_y(), co.get_z()} {}  // Copy constructor
    // Coord<T> operator=(const Coord<T> &co);  // Move operator
    ~Coord() = default;

    T get_x() const { return x; }
    T get_y() const { return y; }
    T get_z() const { return z; }
    T get_magnitude() const;
    void set_x(T x) { this->x = x; }
    void set_y(T y) { this->y = y; }
    void set_z(T z) { this->z = z; }
    // Might need to change these conditions
    bool operator<(const Coord<T> &co) const { return this->z < co.z; }
    bool operator>(const Coord<T> &co) const { return this->z > co.z; }
    bool operator==(const Coord<T> &co) const {
        return this->x == co.get_x() && this->y == co.get_y() &&
               this->z == co.get_z();
    }
    // Unary operators
    Coord<T> operator-(const Coord<T> &rhs) const;  // Subtracting
    Coord<T> operator+(const Coord<T> &co) const;   // Adding
    T operator*(const Coord<T> &co) const;          // dot product
    Coord<T> operator*(const T &i) const;           // Scaling
    Coord<T> operator/(const T &i) const;           // Scaling
    // Cross product
    Coord<T> cross(const Coord<T> &co) const;
    // Normalize the coord
    Coord<T> normalize();
    // Calculate distance from another coord
    double dist(const Coord<T> &co) const;
};

// Calculate cross product between two coords.
template <typename T>
Coord<T> cross(const Coord<T> &lhs, const Coord<T> &rhs);
// Distance between two coords.
template <typename T>
double dist(const Coord<T> &lhs, const Coord<T> &rhs);

#include "Coord.tpp"

#endif  // _COORD_CPP_