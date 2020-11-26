#pragma once
#include <cassert>
using namespace std;

template<typename T>
class Array
{
public:
    Array(int size = 50);                           // 构造函数
    ~Array();                                       // 析构函数
    int getSize() const;                            // 取数组大小
    void resize(int size);                          // 修改数组大小
    
    Array(const Array<T> & arr);                    // 拷贝构造函数
    Array<T> & operator= (const Array<T> & arr);    // 重载"="使数组对象可以整体赋值,需要深拷贝,如果浅拷贝就会导致析构函数中对同一块内存重复释放
    T & operator[] (int i);                         // 重载"[]"，返回的是引用，因为引用可以做左值，同时返回引用也避免了触发拷贝构造带来的开销
    const T & operator[] (int i) const;             // 常对象只能调用常函数所以后面加了const，直接访问常数组中的元素返回的是常量，所以前面加const
    operator T * ();                                // 设计一个函数，这个函数就是让数组对象名字就是数组元素首地址
    operator const T * () const;                    // 常对象只能调用常函数（后const），为避免通过指针修改数组内容，故转换为常指针（前const）
private:
    T * list;   // T 类型指针，用于存放动态分配的数组内存首地址
    int size;   // 数组大小
};

template<typename T>
Array<T>::operator const T * () const
{
    return this->list;
}

template<typename T>
Array<T>::operator T * ()
{
    return this->list;
}

template<typename T>
const T & Array<T>::operator[] (int i) const
{
    assert(i >= 0 && i < this->size);
    return this->list[i];
}

template<typename T>
T & Array<T>::operator[] (int i)
{
    assert(i >= 0 && i < this->size);
    return this->list[i];
}

template<typename T>
Array<T> & Array<T>::operator= (const Array<T> & arr)
{
    // 赋值操作只能是对于两个已经存在的对象之间进行赋值操作
    // 而当做赋值操作的时候，如果被赋值数组的size和要赋值的数组的size不一样大，就会删除被赋值数组对象的原有内存空间然后重新分配的内存空间
    // 所以不能自己给自己赋值，即==>需要对是否是自己给自己赋值做检查
    if (&arr != *this)
    {
        if (this->size != arr.size)
        {
            delete [] this->list;           // 删除数组原有内存
            this->list = new T[arr.size];   // 重新分配size个元素的内存
            this->size = arr.size;          // 更新本数组对象的大小
        }
        for (int i = 0; i < this->size; i ++)
        {
            this->list[i] = arr.list[i];    // 赋值操作
        }
    }
}

template<typename T>
Array<T>::Array(int size)
{
    assert(size >= 0);          // 数组大小应该非负
    this->size = size;
    this->list = new T[size];   // 动态分配元素空间
}

template<typename T>
Array<T>::Array(const Array<T> & arr)
{
    this->size = arr.size;
    this->list = new T[this->size];
    for (int i = 0; i < this->size; i ++)
    {
        this->list[i] = arr.list[i];
    }
}

template<typename T>
Array<T>::~Array()
{
    delete [] this->list;
}

template<typename T>
int Array<T>::getSize() const
{
    return this->size;
}

template<typename T>
void Array<T>::resize(int size)
{
    assert(size >= 0);                              // 检查 size 是否非负
    if (size == this->size)
    {
        return;                                     // 如果指定的大小与原有大小一样，就什么也不做
    }
    T * newList = new T[size];                      // 申请新的数组内存
    int n = size < this->size ? size : this->size;
    for (int i = 0; i < n; i ++)
    {
        newList[i] = this->list[i];
    }
    delete [] this->list;                           // 删除原数组
    this->list = newList;                           // this->list 指向新的内存空间
    this->size = size;                              // 更新数组当前的状态 size
}
