#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "Coord.hpp"
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
        move_z(size * 2);     // move away from screen (at z=0)
        move_y(size * -0.5);  // center in y
        move_x(size * -0.5);  // center in x
    }
};

int main() {
    // const double z1{5}; // Zoom variable

    Cube cube{10};

    // cube.set_proj();
    // cube.print_proj();
    // cube.display();
    // cube.rotate_y(45);
    // cube.set_proj();
    // cube.display();

    while (true) {
        cube.rotate_x(10.0);
        cube.rotate_y(10.0);
        cube.rotate_z(10.0);
        cube.set_proj();
        cube.display();
        this_thread::sleep_for(chrono::seconds(1/60));
    }

    // Testing that stuff works...
    // string
    // test{"........................................................................................................................"};
    // cout << test.size();
    // Coord<double> one{1, 0, 3};
    // Coord<double> two{2, 1, 2};
    // Coord<double> three{one + two};
    // cout << three << endl;  // [ 3, 1, 5]

    // Coord<double> four{one};
    // cout << four << one << endl;  // [ 1, 0, 3 ][ 1, 0, 3 ]

    // Coord<double> five{1, 2, 3};
    // five = four;
    // cout << five << four << endl;  // [ 1, 0, 3 ][ 1, 0, 3 ]
    // five.normalize();
    // cout << five << " " << five.get_magnitude() << endl;  // [ 0.32, 0, 0.95
    // ] 1 cout << one.dist(two) << endl;                        // 1 cout <<
    // dist(one, two) << endl;                       // 1

    return 0;
}