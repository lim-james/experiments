#include <iostream>
#include <vector>

void sort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

int main() {
    std::vector<int> arr;
    
    int n;
    std::cin >> n;

    if (n <= 0) return 0;

    int x; 
    while (n-- > 0) {
        std::cin >> x;
        arr.push_back(x);
    }

    // add sorting algorithm
    sort(arr);

    for (int i = 0; i < arr.size(); ++i) {
        std::cout << (i > 0 ? " " : "") << arr[i];
    }

    std::cout << std::endl;

    return 0;
}
