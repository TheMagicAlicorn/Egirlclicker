#include <iostream>

int main() {
    float a = 0.6f + 0.7f;
    std::cout.precision(32);
    if(a >= 1.3f) {
        std::cout << a << "\n";
        std::cout << "more than";
    } else {
        std::cout << a << "\n";
        std::cout << "less than";
    }
    return 0;
}