#include <print> // c++23

int main(int argsc, const char* argsv[]) {
    for (int i=0; i<argsc; ++i) {
        std::println("{}: {}", i, argsv[i]);
    }
}
