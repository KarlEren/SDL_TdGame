#pragma once


template<class T>//为了可继承，使用模板特化
class Manager
{
public:
    static  T* instance()
    {
        if (!manager)manager = new T();
        return manager;
    }
private:
    static T*manager;
protected:
    Manager()=default;
    ~Manager()=default;
    Manager(const Manager&)=delete;
    Manager& operator=(const Manager&)=delete;
};

template<class T>
T* Manager<T>::manager=nullptr;
