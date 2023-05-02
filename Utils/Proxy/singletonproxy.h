#pragma once 

template<typename T> class SingletonProxy
{
public:
    static void Register(T* instance);
    static void Unregister();
    static T& GetInstance();
private:
    static T* m_Instance;
};

template<typename T>
void SingletonProxy<T>::Register(T* instance)
{
    m_Instance = instance;
}

template<typename T>
void SingletonProxy<T>::Unregister()
{
    m_Instance = nullptr;
}

template<typename T>
T& SingletonProxy<T>::GetInstance()
{
    return *m_Instance;
}

template <typename T>
T* SingletonProxy<T>::m_Instance = nullptr;