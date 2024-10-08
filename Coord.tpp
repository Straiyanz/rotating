#include <cmath>

#include "Coord.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, const Coord<T> co) {
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

/* Unary operators */

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
template <typename T>
T Coord<T>::operator*(const Coord<T> &co) const {
    T x{this->get_x() * co.get_x()};
    T y{this->get_y() * co.get_y()};
    T z{this->get_z() * co.get_z()};
    return x + y + z;
}
template <typename T>
Coord<T> Coord<T>::operator*(const T &i) const {
    return Coord<T>{this->get_x() * i, this->get_y() * i, this->get_z() * i};
}
template <typename T>
Coord<T> Coord<T>::operator/(const T &i) const {
    if (i == 0)
        return *this;
    else
        return Coord<T>{this->get_x() / i, this->get_y() / i,
                        this->get_z() / i};
}

// Utility

template <typename T>
Coord<T> Coord<T>::cross(const Coord<T> &co) const {
    T x, y, z;
    x = this->get_y() * co.get_z() - this->get_z() * co.get_y();
    y = this->get_z() * co.get_x() - this->get_x() * co.get_z();
    z = this->get_x() * co.get_y() - this->get_y() * co.get_x();
    return Coord<T>{x, y, z};
}
template <typename T>
Coord<T> Coord<T>::normalize() {
    T mag = get_magnitude();
    if (mag != 0) *this = *this / mag;
    return *this;
}

// Rotations

template <typename T>
void Coord<T>::rotate_x(double theta) {
    theta *= std::numbers::pi / 180; // convert to radians
    long double sin_t = std::sin(theta);
    long double cos_t = std::cos(theta);
    T old_y = this->get_y();
    this->set_x(old_y * cos_t - this->get_z() * sin_t);
    this->set_y(old_y * sin_t + this->get_z() * cos_t);
}
template <typename T>
void Coord<T>::rotate_y(double theta) {
    theta *= std::numbers::pi / 180; // convert to radians
    long double sin_t = std::sin(theta);
    long double cos_t = std::cos(theta);
    T old_x = this->get_x();
    this->set_x(old_x * cos_t - this->get_z() * sin_t);
    this->set_y(-old_x * sin_t + this->get_z() * cos_t);
}
template <typename T>
void Coord<T>::rotate_z(double theta) {
    theta *= std::numbers::pi / 180; // convert to radians
    long double sin_t = std::sin(theta);
    long double cos_t = std::cos(theta);
    T old_x = this->get_x();
    this->set_x(old_x * cos_t - this->get_y() * sin_t);
    this->set_y(old_x * sin_t + this->get_y() * cos_t);
}
