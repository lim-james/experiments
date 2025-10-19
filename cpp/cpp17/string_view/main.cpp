#include <iostream>
#include <string>
#include <string_view>

void* operator new(size_t size) {
    std::cout << "ALLOCATING " << size << " BYTES\n";
    return malloc(size);
}

int main() {
    const char* c_str = "My name is James Lim, and these are my experiments!!";

    size_t my_name_len = sizeof("My name"); // "My name"
    size_t name_offset = sizeof("My name is");
    size_t name_len = sizeof("James Lim") - 1; // null terminator 
    size_t experiments_offset = sizeof("My name is James Lim,");

    {
        std::string_view substr(c_str, my_name_len);
        std::cout << substr << '\n';
    }
    std::cout << '\n';

    {
        std::string_view substr(c_str + name_offset, name_len); 
        std::cout << substr << '\n';
    }
    std::cout << '\n';

    {
        std::string_view substr(
            c_str + name_offset, 
            c_str + name_offset + name_len
        ); // this constructor only introduced in c++20
        std::cout << substr << '\n';
    }
    std::cout << '\n';

    {
        std::string str{c_str}; // allocating
        std::string_view substr(
            str.begin() + name_offset, 
            str.begin() + name_offset + name_len
        ); // this constructor only introduced in c++20
        std::cout << substr << '\n';
    }
    std::cout << '\n';


    {
        std::string_view substr(
            c_str + experiments_offset
        ); // this constructor only introduced in c++20
        std::cout << substr << '\n';
    }
    std::cout << '\n';

    {
        std::string str(c_str);
        std::string_view substr(
            str.begin() + experiments_offset,
            str.end()
        ); // this constructor only introduced in c++20
        std::cout << substr << '\n';
    }
    std::cout << '\n';

    {
        std::string str{c_str}; // allocating
        std::string substr = str.substr(experiments_offset);
        std::cout << substr << '\n';
    }
    std::cout << '\n';

    {
        std::string_view dangling;
        {
            std::string str(c_str);
            dangling = std::string_view(
                str.begin() + name_offset, 
                str.begin() + name_offset + name_len
            );
            std::cout << "SCOPED: " << dangling << '\n';
        }
        std::cout << "EXPIRED: " << dangling << '\n';
    }
    std::cout << '\n';

    return 0;
}
