#include <iostream>
#include "IntArray.h"
using namespace std;

int main()
{
    int length = -1;

    try
    {
        IntArray array(length);
    }
    
    catch (bad_range& e)
    {
        cout << e.what() << endl;
    }

    catch (bad_length& e)
    {
        cout << e.what() << endl;
    }

    IntArray array(length);
    {
        for (int i = 0; i < length; ++i)
            array[i] = i + 1;

        for (int i = 0; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';

        std::cout << '\n' << '\n';
    }

    array.resize(9);
    {
        for (int i = 0; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';

        std::cout << '\n' << '\n';
    }

    array.insertBefore(55, 9);
    {
        for (int i = 0; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';

        std::cout << '\n' << '\n';
    }
    
    array.remove(0);
    {
        for (int i = 0; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';

        std::cout << '\n' << '\n';
    }

    array.insertAtBeginning(1);
    {
        for (int i = 0; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';

        std::cout << '\n' << '\n';
    }

    array.insertAtEnd(11);
    {
        for (int i = 0; i < array.getLength(); ++i)
            std::cout << array[i] << ' ';

        std::cout << '\n' << '\n';
    }

    {
        IntArray b{ array };
        b = array;
        b = b;
        array = array;
    }

    return 0;
}