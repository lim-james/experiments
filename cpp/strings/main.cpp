#include <iostream>
#include <string>

void* operator new(size_t size) {
    std::cout << "ALLOCATING " << size << " BYTES\n";
    return malloc(size);
}

void print(std::string s) {
    std::cout << s << '\n';
}

int main() {
    {
        // no allocations called, SSO-ed
        std::string s{"hello"}; 
        s += " world";

        std::string copy = s;
        print(s);
    }
    std::cout << '\n';

    {
        std::string s(23, 'a'); // this seems to be the magic number
        print(s);
    }
    std::cout << '\n';

    {
        std::string a(20, 'a'); 
        std::string b(3, 'b');
        std::string c = a + b;
        print(a);
        print(b);
        print(c);
    }

    return 0;
}
