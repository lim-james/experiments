#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void sequential_access(std::vector<int64_t>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] += 1;
    }
}

void random_access(std::vector<int64_t>& arr, size_t access_count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, arr.size() - 1);

    for (size_t i = 0; i < access_count; ++i) {
        size_t index = dis(gen);
        arr[index] += 1;
    }
}

void flush_cache(size_t size_mb) {
    size_t buffer_count = size_mb * 1024 * 1024;
    std::vector<char> buffer(buffer_count);
    for (size_t i = 0; i < buffer_count; ++i) {
        buffer[i] = 'a';
    }
}

int main() {
    const size_t L1D_SIZE = 65536;
    const size_t L2D_SIZE = 4194304;
    const size_t L3D_SIZE = 8 * 1024 * 1024;
    const size_t BAD_SIZE = 80 * 1024 * 1024;
    const size_t I64_SIZE = sizeof(int64_t);

    const size_t RANDOM_ACCESS_COUNT = 2000000;

    size_t sizes[] = { 
        L1D_SIZE / I64_SIZE, 
        L2D_SIZE / I64_SIZE,
        L3D_SIZE / I64_SIZE,
        BAD_SIZE / I64_SIZE 
    };

    for (auto size: sizes) {
        std::vector<int64_t> mem(size);
        std::cout << ">>> " << size << " elements\n";

        flush_cache(256);

        auto start = std::chrono::high_resolution_clock::now();
        sequential_access(mem);
        auto end = std::chrono::high_resolution_clock::now();
        auto sequential_duration = std::chrono::duration<double>(end - start).count();
        std::cout << "sequential access = " << sequential_duration << '\n';

        flush_cache(256);

        start = std::chrono::high_resolution_clock::now();
        random_access(mem, RANDOM_ACCESS_COUNT);
        end = std::chrono::high_resolution_clock::now();
        auto random_duration = std::chrono::duration<double>(end - start).count();
        std::cout << "random access     = " << random_duration << '\n';

    }

    

    return 0;
}
