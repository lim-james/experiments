#include <iostream>
#include <vector>

template<typename T>
void sort(std::vector<T>& arr) {
    size_t sorted = 0;
    while (++sorted != arr.size()) {
        T x = arr[sorted];

        size_t i = sorted - 1;
        while (i >= 0 && arr[i] > x) {
            arr[i + 1] = arr[i];        
            --i;
        }
        arr[i + 1] = x;
    }
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
