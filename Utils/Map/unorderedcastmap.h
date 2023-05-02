#pragma once 

#include <iterator>

template<typename Key, typename Value, typename KeyCast>
class UnorderedCastMap
{
public:
    Value& Get(Key key){ return m_Map.at(static_cast<KeyCast>(key));}
    void Set(Key key, Value value) { m_Map.emplace(static_cast<KeyCast>(key), value);}
    void Emplace(Key key, Value value) { m_Map.emplace(static_cast<KeyCast>(key), std::move(value));}

    bool Exist(Key key) { return m_Map.find(static_cast<KeyCast>(key)) != m_Map.end(); }
    void Clear() { m_Map.clear(); }

    //Iterators
    typename std::unordered_map<KeyCast, Value>::iterator begin() { return m_Map.begin();}
    typename std::unordered_map<KeyCast, Value>::const_iterator begin() const { return m_Map.begin();}
    typename std::unordered_map<KeyCast, Value>::iterator end() { return m_Map.end();}   
    typename std::unordered_map<KeyCast, Value>::const_iterator end() const { return m_Map.end();}  

private:
    std::unordered_map<KeyCast, Value> m_Map;
};