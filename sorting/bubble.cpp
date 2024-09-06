#include <iostream>
#include <vector>

template<typename T>
void sort(std::vector<T>& arr) {
    bool swap = false;
    auto end = arr.end();
    do {
        swap = false;
        --end; 
        for (auto it = arr.begin(); it != end; ++it) {
            if (*it > *(it + 1)) {
                T temp = *it;
                *it = *(it + 1);
                *(it + 1) = temp;
                swap = true;
            }
        }
    } while (swap || end == arr.begin());
}

int main() {
    int n;
    std::cin >> n;

    if (n <= 0) return 0;
    
    std::vector<int> arr(n);

    for (auto it = arr.begin(); it != arr.end(); ++it)
        std::cin >> *it;

    // add sorting algorithm
    sort(arr);

    for (int& a: arr)
        std::cout << a << " ";

    std::cout << std::endl;

    return 0;
}
