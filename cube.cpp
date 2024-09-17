#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Coord.hpp"
#include "Shape.hpp"

using namespace std;

class Cube : public Shape {
   public:
    Cube(int size) : Shape(50/size, size) {
        // iterate over x
        for (int x{}; x < size; x++) {
            // iterate over y
            for (int y{}; y < size; y++) {
                // iterate over z
                for (int z{}; z < size; z++) {
                    // If x, y, z are zero or size-1, this is a face so add to
                    // positions
                    if (x == 0 || x == size - 1 || y == 0 || y == size - 1 ||
                        z == 0 || z == size - 1) {
                        pos.push_back(Coord<int>{x, y, z});
                    }
                }
            }
        }
        move_z(size *1.1);     // move away from screen (at z=0)
        move_x(size * -0.5);  // center the cube
    }
};

int main() {
    // const double z1{5}; // Zoom variable

    // Cube cube{2};
    // cout << setprecision(2);
    // cube.print_pos();
    // cube.rotate_x(90);
    // cube.print_pos();
    // cube.print_proj();


    // while (true) {
    //     cube.rotate_x(1.0);
    //     cube.rotate_y(1.0);
    //     cube.display();
    // }

    // Testing that stuff works...
    Coord one{1, 0, 3};
    Coord two{2, 1, 2};
    Coord three{one * two};
    cout << three << endl;

    Coord four{one};
    cout << four << one << endl;

    Coord five{1, 2, 3};
    five = four;
    cout << five << four << endl;

    return 0;
}