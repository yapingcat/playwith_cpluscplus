#include "gostring.h"
#include <iostream>

using namespace std;

void testcount1()
{
    cout << gostring::count("caoyaping", "a") << endl;
    cout << gostring::count("caoyaping", "ca") << endl;
    cout << gostring::count("hellllo", "ll") << endl;
}

void testcount2()
{
    cout << gostring::count("hello world", "") << endl;
    cout << gostring::count("", "") << endl;
    cout << gostring::count("", "xx") << endl;
}

void testequalfold()
{
    cout << std::boolalpha << gostring::equalfold("CPP", "cpp") << endl;
    cout << std::boolalpha << gostring::equalfold("GOlang", "golang") << endl;
    cout << std::boolalpha << gostring::equalfold("ccc", "CCCc") << endl;
    cout << std::boolalpha << gostring::equalfold("", "xx") << endl;
    cout << std::boolalpha << gostring::equalfold("xx", "") << endl;
    cout << std::boolalpha << gostring::equalfold("xx", "xx") << endl;
    cout << std::boolalpha << gostring::equalfold("xx&&", "xx&&") << endl;
    cout << std::boolalpha << gostring::equalfold("x#X&&", "x#x&&") << endl;
}

void testfields()
{
    auto vec = gostring::fields("hello world");

    auto display = [&vec]()
    {
        for (auto &&s : vec)
        {
            cout << s << endl;
        }
    };

    vec = gostring::fields("hello wor ld");
    display();

    vec = gostring::fields("helloworld");
    display();

    vec = gostring::fields("  hello w   orld  ");
    display();
}

int main()
{
    testcount1();
    testcount2();
    testequalfold();
    testfields();

    return 0;
}