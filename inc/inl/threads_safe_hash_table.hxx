#ifndef SAFE_HASH_TABLE_HXX
#define SAFE_HASH_TABLE_HXX

#include "threads_safe_hash_table.hpp"

namespace threads {

template <typename K, typename V>
SafeHashTable<K,V>::SafeHashTable()
: m_map()
, m_mtx()
, m_mtxMap()
{
}

template <typename K, typename V>
void SafeHashTable<K,V>::earseMutexIfNeeded(K const& a_key, std::shared_ptr<std::shared_mutex>& a_sharedPtr) const
{
    std::lock_guard<std::mutex> guard(m_mtx);
    if(a_sharedPtr.use_count() == 2) {
        m_mtxMap.erase(a_key);
    }
}


template <typename K, typename V>
std::shared_ptr<std::shared_mutex> SafeHashTable<K,V>::findOrGenerateSharedPtrToMutex(K const& a_key) const
{
    typename MtxMap::iterator itr;
    SharedPtr sharedPtr;
    {
        std::lock_guard<std::mutex> guard(m_mtx);
        itr = m_mtxMap.find(a_key);
        if(itr == m_mtxMap.cend()) { //not found
            m_mtxMap[a_key] = std::make_shared<std::shared_mutex>();
        }
        sharedPtr = m_mtxMap[a_key];
    }
    return sharedPtr;
}


template <typename K, typename V>
const V& SafeHashTable<K,V>::Get(K const& a_key) const
{
    SharedPtr sharedPtr = findOrGenerateSharedPtrToMutex(a_key);

    V result;
    {
        std::lock_guard<std::shared_mutex> guard(*sharedPtr);
        try {
            result = m_map.at(a_key);
        }
        catch (...) {
            throw std::runtime_error("key not exist");
        }
    }
    
    earseMutexIfNeeded(a_key, std::ref(sharedPtr));
    return result;
}


template <typename K, typename V>
size_t SafeHashTable<K,V>::Count(K const& a_key) const
{
    SharedPtr sharedPtr = findOrGenerateSharedPtrToMutex(a_key);

    size_t result = 0;
    {
        std::shared_lock<std::shared_mutex> guard(*sharedPtr);
        result = m_map.count();
    }
    
    earseMutexIfNeeded(a_key, std::ref(sharedPtr));
    return result;
}


template <typename K, typename V>
bool SafeHashTable<K,V>::Containes(K const& a_key) const
{
    SharedPtr sharedPtr = findOrGenerateSharedPtrToMutex(a_key);

    bool result;
    {
        std::shared_lock<std::shared_mutex> guard(*sharedPtr);
        result = (m_map.find(a_key) != m_map.end());
    }
    
    earseMutexIfNeeded(a_key, std::ref(sharedPtr));
    return result;
}


template <typename K, typename V>
void SafeHashTable<K,V>::Insert(K const& a_key, V const& a_val)
{
    SharedPtr sharedPtr = findOrGenerateSharedPtrToMutex(a_key);

    {
        std::lock_guard<std::shared_mutex> guard(*sharedPtr);
        m_map.insert({a_key, a_val});
    }
    
    earseMutexIfNeeded(a_key, std::ref(sharedPtr));
} 


template <typename K, typename V>
bool SafeHashTable<K,V>::Erase(K const& a_key)
{
    SharedPtr sharedPtr = findOrGenerateSharedPtrToMutex(a_key);
    typename std::unordered_map<K,V>::size_type result = 0;
    {
        std::lock_guard<std::shared_mutex> guard(*sharedPtr);
        result = m_map.erase(a_key);
    }
    
    earseMutexIfNeeded(a_key, std::ref(sharedPtr));
    return (result == 1);
}

template <typename K, typename V>
bool SafeHashTable<K,V>::Update(K const& a_key, V const& a_val)
{
    SharedPtr sharedPtr = findOrGenerateSharedPtrToMutex(a_key);

    bool result = true;

    {
        std::lock_guard<std::shared_mutex> guard(*sharedPtr);
        try {
            m_map.at(a_key) = a_val;
        }
        catch (...) {
            result = false;
        }
        
    }
    
    earseMutexIfNeeded(a_key, std::ref(sharedPtr));
    return result;
}

#ifdef DEBUG
template <typename K, typename V>
size_t SafeHashTable<K,V>::GetSizeOfMutexHash() const
{
    std::lock_guard<std::mutex> guard(m_mtx);
    return m_mtxMap.size();
}


template <typename K, typename V>
void SafeHashTable<K,V>::Print() const
{
    for (auto const &pair: m_map) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

#endif

} //threads

#endif // SAFE_HASH_TABLE_HXX




