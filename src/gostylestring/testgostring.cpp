#include "gostring.h"
#include <iostream>

using namespace std;

void testcount1()
{
    cout << "================testcount1===============" << endl;
    cout << gostring::count("caoyaping", "a") << endl;
    cout << gostring::count("caoyaping", "ca") << endl;
    cout << gostring::count("hellllo", "ll") << endl;
    cout << "================testcount1===============" << endl;
}

void testcount2()
{
    cout << "================testcount2===============" << endl;
    cout << gostring::count("hello world", "") << endl;
    cout << gostring::count("", "") << endl;
    cout << gostring::count("", "xx") << endl;
    cout << "================testcount2===============" << endl;
}

void testequalfold()
{
    cout << "================testequalfold===============" << endl;
    cout << std::boolalpha << gostring::equalfold("CPP", "cpp") << endl;
    cout << std::boolalpha << gostring::equalfold("GOlang", "golang") << endl;
    cout << std::boolalpha << gostring::equalfold("ccc", "CCCc") << endl;
    cout << std::boolalpha << gostring::equalfold("", "xx") << endl;
    cout << std::boolalpha << gostring::equalfold("xx", "") << endl;
    cout << std::boolalpha << gostring::equalfold("xx", "xx") << endl;
    cout << std::boolalpha << gostring::equalfold("xx&&", "xx&&") << endl;
    cout << std::boolalpha << gostring::equalfold("x#X&&", "x#x&&") << endl;
    cout << "================testequalfold===============" << endl;
}

void testfields()
{
    cout << "================testfields===============" << endl;

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
    cout << "================testfields===============" << endl;
}

void testhasPrefix()
{
    cout << "================testhasPrefix===============" << endl;
    cout << std::boolalpha << gostring::hasPrefix("", "") << endl;
    cout << std::boolalpha << gostring::hasPrefix("", "xx") << endl;
    cout << std::boolalpha << gostring::hasPrefix("cyp", "") << endl;
    cout << std::boolalpha << gostring::hasPrefix("cyp", "kkk") << endl;
    cout << std::boolalpha << gostring::hasPrefix("cyp", "cy") << endl;
    cout << std::boolalpha << gostring::hasPrefix("cypkkk", "cypkkk") << endl;
    cout << std::boolalpha << gostring::hasPrefix("cypkkk", "c") << endl;
    cout << std::boolalpha << gostring::hasPrefix("cy", "cyp") << endl;
    cout << "================testhasPrefix===============" << endl;
}

void testhasSuffix()
{
    cout << "================testhasSuffix===============" << endl;
    cout << std::boolalpha << gostring::hasSuffix("", "") << endl;
    cout << std::boolalpha << gostring::hasSuffix("", "xx") << endl;
    cout << std::boolalpha << gostring::hasSuffix("cyp", "") << endl;
    cout << std::boolalpha << gostring::hasSuffix("cyp", "kkk") << endl;
    cout << std::boolalpha << gostring::hasSuffix("cyp", "yp") << endl;
    cout << std::boolalpha << gostring::hasSuffix("cypkkk", "cypkkk") << endl;
    cout << std::boolalpha << gostring::hasSuffix("cypkkk", "k") << endl;
    cout << std::boolalpha << gostring::hasSuffix("yp", "cyp") << endl;
    cout << "================testhasSuffix===============" << endl;
}

void testcontains()
{
    cout << "================testcontains===============" << endl;
    cout << std::boolalpha << gostring::contains("", "") << endl;
    cout << std::boolalpha << gostring::contains("", "xx") << endl;
    cout << std::boolalpha << gostring::contains("xx", "") << endl;
    cout << std::boolalpha << gostring::contains("xxtt", "xt") << endl;
    cout << std::boolalpha << gostring::contains("xf", "xfxf") << endl;
    cout << "================testcontains===============" << endl;
}

void testcontainsAny()
{
    cout << "================testcontainsAny===============" << endl;
    cout << std::boolalpha << gostring::containsAny("", "") << endl;
    cout << std::boolalpha << gostring::containsAny("", "xx") << endl;
    cout << std::boolalpha << gostring::containsAny("xx", "") << endl;
    cout << std::boolalpha << gostring::containsAny("xxtt", "xt") << endl;
    cout << std::boolalpha << gostring::containsAny("xf", "zv") << endl;
    cout << "================testcontainsAny===============" << endl;
}

void testindex()
{
    cout << "================testindex===============" << endl;
    cout << std::dec << gostring::index("", "") << endl;
    cout << std::dec << gostring::index("", "xx") << endl;
    cout << std::dec << gostring::index("hello", "") << endl;
    cout << std::dec << gostring::index("hello world", "wo") << endl;
    cout << std::dec << gostring::index("hello", "world") << endl;
    cout << "================testindex===============" << endl;
}

void testindexByte()
{
    cout << "================testindexByte===============" << endl;
    cout << std::dec << gostring::indexByte("", 'c') << endl;
    cout << std::dec << gostring::indexByte("x", 'c') << endl;
    cout << std::dec << gostring::indexByte("hello", 'c') << endl;
    cout << std::dec << gostring::indexByte("hello world", 'w') << endl;
    cout << "================testindexByte===============" << endl;
}

void testindexAny()
{
    cout << "================testindexAny===============" << endl;

    cout << std::dec << gostring::indexAny("", "") << endl;
    cout << std::dec << gostring::indexAny("", "xx") << endl;
    cout << std::dec << gostring::indexAny("hello", "") << endl;
    cout << std::dec << gostring::indexAny("hello world", "wo") << endl;
    cout << std::dec << gostring::indexAny("hello", "world") << endl;
    cout << std::dec << gostring::indexAny("hello", "xyz") << endl;
    cout << "================testindexAny===============" << endl;
}

void testindexFunc()
{
    cout << "================testindexFunc===============" << endl;

    cout << std::dec << gostring::indexFunc("", [](const char &c)
                                            {
                                                if (c == 'c')
                                                    return true;
                                                else
                                                    return false;
                                            })
         << endl;

    cout << std::dec << gostring::indexFunc("cc", [](const char &c)
                                            {
                                                if (c == 'c')
                                                    return true;
                                                else
                                                    return false;
                                            })
         << endl;

    cout << std::dec << gostring::indexFunc("xyz", [](const char &c)
                                            {
                                                if (c == 'c')
                                                    return true;
                                                else
                                                    return false;
                                            })
         << endl;
    cout << "================testindexFunc===============" << endl;
}

int main()
{
    testcount1();
    testcount2();
    testequalfold();
    testfields();
    testhasPrefix();
    testhasSuffix();
    testcontains();
    testcontainsAny();
    testindex();
    testindexByte();
    testindexAny();
    testindexFunc();
    return 0;
}