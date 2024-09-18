#include <cmath>

#include "Coord.hpp"

template <typename U>
std::ostream &operator<<(std::ostream &os, const Coord<U> co) {
    os << "[ ";
    os << co.get_x() << ", ";
    os << co.get_y() << ", ";
    os << co.get_z() << " ]";
    return os;
}

// Getters
template <typename T>
T Coord<T>::get_magnitude() const {
    return std::sqrt(std::pow(this->get_x(), 2) + std::pow(this->get_y(), 2) +
                     std::pow(this->get_z(), 2));
}

// Unary operators
template <typename T>
Coord<T> Coord<T>::operator-(const Coord<T> &co) const {
    T x{this->get_x() - co.get_x()};
    T y{this->get_y() - co.get_y()};
    T z{this->get_z() - co.get_z()};
    return Coord<T>{x, y, z};
}
template <typename T>
Coord<T> Coord<T>::operator+(const Coord<T> &co) const {
    T x{this->get_x() + co.get_x()};
    T y{this->get_y() + co.get_y()};
    T z{this->get_z() + co.get_z()};
    return Coord<T>{x, y, z};
}
// Dot product
template <typename T>
T Coord<T>::operator*(const Coord<T> &co) const {
    T x{this->get_x() * co.get_x()};
    T y{this->get_y() * co.get_y()};
    T z{this->get_z() * co.get_z()};
    return x + y + z;
}
// Scaling
template <typename T>
Coord<T> Coord<T>::operator*(const T &i) const {
    if (i == 0)
        return *this;
    else
        return Coord<T>{this->get_x() * i, this->get_y() * i,
                        this->get_z() * i};
}
// Scaling
template <typename T>
Coord<T> Coord<T>::operator/(const T &i) const {
    if (i == 0)
        return *this;
    else
        return Coord<T>{this->get_x() / i, this->get_y() / i,
                        this->get_z() / i};
}
// Cross Product
template <typename T>
Coord<T> Coord<T>::cross(const Coord<T> &co) const {
    T x, y, z;
    x = this->get_y() * co.get_z() - this->get_z() * co.get_y();
    y = this->get_z() * co.get_x() - this->get_x() * co.get_z();
    z = this->get_x() * this->get_y() - this->get_y() * co.get_x();
    return Coord<T>{x, y, z};
}
// Cross Product between two coords
template <typename T>
Coord<T> cross(const Coord<T> &lhs, const Coord<T> &rhs) {
    T x, y, z;
    x = lhs.get_y() * rhs.get_z() - lhs.get_z() * rhs.get_y();
    y = lhs.get_z() * rhs.get_x() - lhs.get_x() * rhs.get_z();
    z = lhs.get_x() * lhs.get_y() - lhs.get_y() * rhs.get_x();
    return Coord<T>{x, y, z};
}

// Normalize
template <typename T>
Coord<T> Coord<T>::normalize() {
    T mag = get_magnitude();
    if (mag != 0) *this = *this / mag;
    return *this;
}

// Distance functions
template <typename T>
double Coord<T>::dist(const Coord<T> &co) const {
    return (*this - co).get_magnitude();
}

// Distance from LHS to RHS
template <typename T>
double dist(const Coord<T> &lhs, const Coord<T> &rhs) {
    return (lhs - rhs).get_magnitude();
}
