#include <bits/stdc++.h>
using namespace std;

class Singleton
{
    Singleton()
    {
        cout << "Singleton Instance created";
    }

public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }

    void showMessage()
    {
        std::cout << "Hello from Singleton!\n";
    }
};

int main()
{
    Singleton &s1 = Singleton::getInstance();
    s1.showMessage();

    Singleton &s2 = Singleton::getInstance();

    std::cout << "Same instance? " << (&s1 == &s2) << "\n"; // Prints 1
}
