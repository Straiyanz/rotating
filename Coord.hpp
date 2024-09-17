#ifndef _COORD_CPP_
#define _COORD_CPP_
#include <iostream>

template <typename T>
class Coord {
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Coord<U> co);

   private:
    T x, y, z;

   public:
    Coord(T x, T y, T z) : x(x), y(y), z(z) {}
    Coord(T x, T y) : Coord<T>(x, y, 0) {}  // for 2d stuffs
    // Coord(Coord<T> &&co) noexcept;          // Move constructor
    // Coord(const Coord<T> &co);               // Copy constructor
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
        return this->x == co.x && this->y == co.y && this->z == co.z;
    }
    // Unary operators
    Coord<T> operator-(const Coord<T> &rhs) const;
    Coord<T> operator+(const Coord<T> &co) const;
    Coord<T> operator*(const Coord<T> &co) const;
    Coord<T> operator*(int &i) const;
    // Cross products
    Coord<T> cross(const Coord<T> &co) const;
    Coord<T> cross(const Coord<T> &lhs, const Coord<T> &rhs);
};

#include "Coord.tpp"

#endif  // _COORD_CPP_