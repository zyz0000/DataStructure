//
// Created by dell on 2021/7/24.
//

//顺序表类的声明
#ifndef DS_SEQLIST_H
#define DS_SEQLIST_H

#include <iostream>
#include <cstdlib>
#include "LinearList.h"
using namespace std;


const int defaultSize = 100;
template<typename T>
class SeqList: public LinearList<T>{
protected:
    T* data;    //存放数组
    int maxSize;    //最大可容纳表的项数
    int last;   //当前已存表项的最后位置
    void reSize(int newSize);   //改变data数组空间大小
public:
    SeqList(int sz = defaultSize);  //构造函数
    SeqList(SeqList<T>& L); //复制构造函数
    ~SeqList() {delete [] data;}    //析构函数
    int Size()const {return maxSize;}   //计算可容纳表项的个数
    int Length()const {return last + 1;}    //计算表长度
    int Search(T& x)const;  //搜索x在表中的位置
    int Locate(int i)const; //定位第i个表项

    bool getData(int i, T& x)const{
        if (i > 0 && i <= last + 1){
            x = data[i - 1];
            return true;
        }
        else{
            return false;
        }
    }   //取出第i个表项的值

    void setData(int i, T& x){
        if (i > 0 && i <= last + 1){
            data[i - 1] = x;
        }
    }   //用x修改第i个表项

    bool Insert(int i, T& x);   //在第i个表项之后插入x
    bool Remove(int i, T& x);   //删除第i个表项，通过x返回其值
    bool IsEmpty() {return (last == -1)? true:false;}   //判断表是否为空
    bool IsFull() {return (last == maxSize - 1)? true:false;}   //判断表是否为满

    void input();   //输入
    void output();  //输出
    SeqList<T> operator=(SeqList<T>& L);    //表整体赋值
};


// 构造函数的实现
template<typename T>
SeqList<T>::SeqList(int sz) {
    if (sz > 0){
        maxSize = sz;
        last = -1;
        data = new T[maxSize];
        if (data == nullptr){
            cerr << "存储分配错误." << endl;
            exit(1);    //结束程序，状态值为1
        }
    }
}


//复制构造函数的实现
template<typename T>
SeqList<T>::SeqList(SeqList<T> &L) {
    maxSize = L.Size();
    last = L.Length() - 1;
    T value;
    data = new T[maxSize];
    if (data == nullptr){
        cerr << "存储分配错误." << endl;
        exit(1);    //结束程序，状态值为1
    }
    for (int i = 0; i <= last + 1; i++){
        L.getData(i, value);
        data[i - 1] = value;
    }
}


template<typename T>
void SeqList<T>::reSize(int newSize) {
    //私有函数，扩充顺序表的存储数组空间大小，新数组的元素个数为newSize
    if (newSize <= 0){
        cerr << "无效的数组大小." << endl;
        exit(1);
    }
    if (newSize != maxSize){
        T* newarray = new T[newSize];
        if (newarray == nullptr){
            cerr << "存储分配错误." << end;
            exit(1);
        }
        int n = last + 1;
        T* srcptr = data;   //源数组首地址
        T* destptr = newarray;  //目标数组首地址
        while (n--){
            *destptr++ = *srcptr++; //逐一复制对应元素
        }
        delete [] data; //删除老数组
        data = newarray;    //复制新数组
        maxSize = newSize;
    }
}


template<typename T>
int SeqList<T>::Search(T &x) const {
    //搜索操作，若找到则返回x是表的第几个元素，否则返回0
    for (int i = 0; i <= last; i++){
        if (data[i] == x){
            return i + 1;
        }
    }
    return 0;
}


template<typename T>
int SeqList<T>::Locate(int i) const {
    //定位函数，函数返回第i个表项的位置，否则函数返回0，表示定位失败
    if (i >= 1 && i <= last + 1)
        return i;
    else return 0;
}


template<typename T>
bool SeqList<T>::Insert(int i, T &x) {
    //将新元素x插入到表中第i个表项之后
    if (last == maxSize - 1) return false;  //表满，不能再插入
    if (i < 0 || i > last + 1) return false;    //参数i不合理，不能插入
    for (int j = last; j >= i; j--){
        data[j + 1] = data[j];
    }
    data[i] = x;
    last++;
    return true;
}


template<typename T>
bool SeqList<T>::Remove(int i, T &x) {
    //删除表中第i个表项，通过引用型参数x返回删除元素的值
    if (last == -1) return false;   //表空，不能删除
    if (i < 1 || i > last + 1) return false;    //参数i不合理，不能删除
    x = data[i - 1];
    for (int j = i; j <= last; j++){
        data[j - 1] = data[j];
    }
    last--;
    return true;
}
#endif //DS_SEQLIST_H
