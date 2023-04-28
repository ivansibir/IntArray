#pragma once
#include <iostream>
#include <exception>
#ifndef INTARRAY_H
#define INTARRAY_H
using namespace std;

class bad_range : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "Exception: You are out of range.";
    }
};

class bad_length : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "Exception: The length of the array is not suitable.";
    }
};

class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length) : m_length(length)
    {
        if (length <= 0)
        {
            throw bad_length();
        }

        else m_data = new int[length];
        //cout << "A new array has been created." << endl;
    }

    void reallocate(int newLength)
    {
        erase();

        m_length = newLength;
        m_data = new int[newLength];

        if (newLength <= 0)
           return;
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data{ new int[newLength] };

        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };

            for (int index{ 0 }; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }
    
    IntArray(const IntArray& a)
    {
        reallocate(a.getLength());

        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = a.m_data[index];
    }

    IntArray& operator = (const IntArray& a)
    {
        if (&a == this)
            return *this;

        reallocate(a.getLength());

        for (int index{ 0 }; index < m_length; ++index)
            m_data[index] = a.m_data[index];
        
        return *this;
    }

    void insertBefore(int value, int index)
    {
        if (index <= 0 && index >= m_length)
        {
            throw bad_range();
        }

        int* data{ new int[m_length + 1] };

        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        data[index] = value;

        for (int after{ index }; after < m_length; ++after)
            data[after + 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        if (index <= 0 && index >= m_length)
        {
            throw bad_length();
        }

        if (m_length == 1)
        {
            erase();
            return;
        }

        int* data{ new int[m_length - 1] };

        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];

        for (int after{ index + 1 }; after < m_length; ++after)
            data[after - 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const { return m_length; }

    int& operator[](int index)
    {
        if (index <= 0 && index >= m_length)
        {
            throw bad_length();
        }
        return m_data[index];
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

};
#endif