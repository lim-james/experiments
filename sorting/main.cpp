#include <iostream>
#include <vector>

void sort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
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
