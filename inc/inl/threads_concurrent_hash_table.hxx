#ifndef CONCURRENT_HASH_TABLE_HXX
#define CONCURRENT_HASH_TABLE_HXX

#include "threads_concurrent_hash_table.hpp"

namespace threads {

template <typename K, typename V, typename Hash>
ConcurrentHashTable<K,V,Hash>::ConcurrentHashTable()
: m_map()
, m_mtx()
{
}

template <typename K, typename V, typename Hash>
ConcurrentHashTable<K,V,Hash>::ConcurrentHashTable(ConcurrentHashTable const& a_other)
: m_map(a_other.m_map)
, m_mtx()
{
}

template <typename K, typename V, typename Hash>
V ConcurrentHashTable<K,V,Hash>::Get(K const& a_key) const
{
    std::shared_lock<std::shared_mutex> guard(m_mtx);
    try {
        V result;
        result = m_map.at(a_key);
        return result;
    }
    catch (...) {
        throw std::runtime_error("key not exist");
    }   
}

template <typename K, typename V, typename Hash>
size_t ConcurrentHashTable<K,V,Hash>::Count(K const& a_key) const
{
    std::shared_lock<std::shared_mutex> guard(m_mtx);
    size_t result = m_map.count();
    return result;
}

template <typename K, typename V, typename Hash>
bool ConcurrentHashTable<K,V,Hash>::Containes(K const& a_key) const
{
    std::shared_lock<std::shared_mutex> guard(m_mtx);
    bool result = (m_map.find(a_key) != m_map.end());
    return result;
}

template <typename K, typename V, typename Hash>
void ConcurrentHashTable<K,V,Hash>::Insert(K const& a_key, V const& a_val)
{
    std::lock_guard<std::shared_mutex> guard(m_mtx);
    m_map.insert({a_key, a_val});
} 

template <typename K, typename V, typename Hash>
bool ConcurrentHashTable<K,V,Hash>::Erase(K const& a_key)
{
    std::lock_guard<std::shared_mutex> guard(m_mtx);
    typename std::unordered_map<K,V>::size_type result = m_map.erase(a_key);
    return (result == 1);
}

template <typename K, typename V, typename Hash>
bool ConcurrentHashTable<K,V,Hash>::Update(K const& a_key, V const& a_val)
{
    std::lock_guard<std::shared_mutex> guard(m_mtx);
    try {
        m_map.at(a_key) = a_val;
        return true;
    }
    catch(...) {
        return false;
    }
}

template <typename K, typename V, typename Hash>
template <typename Creator, typename Updator>
void ConcurrentHashTable<K,V,Hash>::Upsert(K const& a_key, Creator a_creator, Updator a_updator)
{
    std::lock_guard<std::shared_mutex> guard(m_mtx);
    if(m_map.find(a_key) != m_map.end()) {
        a_updator(m_map[a_key]);
    }
    else {
        m_map.insert({a_key, a_creator()});
    }
}

#ifdef DEBUG

template <typename K, typename V, typename Hash>
void ConcurrentHashTable<K,V>::Print() const
{
    for (auto const &pair: m_map) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

#endif

} //threads

#endif // CONCURRENT_HASH_TABLE_HXX




