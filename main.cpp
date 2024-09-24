#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <thread>
#include <vector>

#include "Shape.hpp"

using namespace std;

class Cube : public Shape {
   public:
    Cube(double size) : Shape(size) {
        // iterate over x
        for (double x{}; x < size; x++) {
            // iterate over y
            for (double y{}; y < size; y++) {
                // iterate over z
                for (double z{}; z < size; z++) {
                    // If x, y, z are zero or size-1, this is a face so add to
                    // positions
                    if (x == 0 || x == size - 1 || y == 0 || y == size - 1 ||
                        z == 0 || z == size - 1) {
                        pos.push_back(Coord<double>{x, y, z});
                    }
                }
            }
        }
        // Center cube on (0,0,0)
        move_z(size * -0.5);  // move away from screen (at z=0)
        move_y(size * -0.5);  // center in y
        move_x(size * -0.5);  // center in x
    }
};

class Sphere : public Shape {
   public:
    Sphere(int radius) : Shape(radius * 2) {}
};

int main() {
    Cube cube{10};
    // cube.print_pos();
    // cube.set_proj();
    // cube.print_proj();

    // while (true) {
    //     cube.set_proj();
    //     cube.display();
    //     cube.rotate_x(10.0);
    //     cube.rotate_y(10.0);
    //     cube.rotate_z(10.0);
    //     // this_thread::sleep_for(chrono::seconds(1/60));
    // }

    // Testing that stuff works...
    {
        cout << "\nCoord Testing:" << endl;
        cout << "====================================" << endl;
        Coord<double> one{1, 1, 2};
        Coord<double> two{2, 0, 0};
        Coord<double> three{one + two};
        cout << "Addition: ";
        cout << three << endl;  // [ 3, 1, 5]
        cout << "Scaling: ";
        cout << three * 4 << endl;
        cout << three / 2 << endl;

        Coord<double> four{one};
        cout << four << one << endl;  // [ 1, 0, 3 ][ 1, 0, 3 ]

        Coord<double> five{1, 2, 3};
        five = four;
        cout << five << four << endl;  // [ 1, 0, 3 ][ 1, 0, 3 ]
        five.normalize();
        cout << five << " " << five.get_magnitude()
             << endl;                    // [ 0.32, 0, 0.95 ]
        cout << one.dist(two) << endl;   // 1
        cout << dist(one, two) << endl;  // 1
    }
    {
        cout << "\nRotation Testing:" << endl;
        cout << "====================================" << endl;
        Coord<double> c1{1, 1, 0};
        cout << "Before 90* rotation around Z: " << c1 << endl;
        c1.rotate_z(90.0);
        cout << "After 90* rotation around Z: " << c1 << endl;
    }
    {
        cout << "\nCross Prod Testing:" << endl;
        cout << "====================================" << endl;
        Coord<double> c1{1, 0, 0};
        Coord<double> c2{0, 1, 0};
        cout << "Should be [ 0, 0, 1 ] : " << cross(c1, c2) << endl;
        cout << "Should be [ 0, 0, -1 ] : " << cross(c2, c1) << endl;
        c1.set_y(1.59);
        cout << "Should be [ 0, 0, 1 ] : " << cross(c1, c2) << endl;
        cout << "Should be [ 0, 0, -1 ] : " << cross(c2, c1) << endl;
        c1 = Coord<double>{1, 1, 1};
        c2 = Coord<double>{0, 1, 0};
        cout << "Should be [-1, 0, 1]: " << cross(c1, c2) << endl;
        cout << "Should be [1, 0, -1]: " << cross(c2, c1) << endl;
    }
    {
        cout << "\nNormal Testing:" << endl;
        cout << "====================================" << endl;
        Coord c1{0, 0, 0};
        Coord c2{1, 1, 0};
        Coord c3{0, 1, 0};
        cout << "Should be [ 0, 0, 1 ]: " << c1.get_normal(c2, c3) << endl;
        cout << "Should be [ 0, 0, -1 ]: " << c1.get_normal(c3, c2) << endl;
    }
    {
        cout << "\nProjection Testing:" << endl;
        cout << "====================================" << endl;
        Cube cub{3};
        cub.print_pos();
        cub.set_proj();
        cub.print_proj();
        // cub.display();
    }
    return 0;
}