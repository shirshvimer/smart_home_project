#ifndef CONCURRENT_HASH_TABLE_HPP
#define CONCURRENT_HASH_TABLE_HPP

#include <unordered_map>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <functional>

namespace threads {

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentHashTable {
public:
    ConcurrentHashTable();
    ConcurrentHashTable(ConcurrentHashTable const& a_other);
	ConcurrentHashTable& operator=(ConcurrentHashTable const&) = delete;
	~ConcurrentHashTable() = default;

    V Get(K const& a_key) const;
    size_t Count(K const& a_key) const;
    bool Containes(K const& a_key) const;
    
    void Insert(K const& a_key, V const& a_val);
    bool Erase(K const& a_key);
    bool Update(K const& a_key, V const& a_val);

    template <typename Creator, typename Updator>
    void Upsert(K const& a_key, Creator a_creator, Updator a_updator);

    #ifdef DEBUG
        void Print() const;
		size_t GetSizeOfMutexHash() const;
	#endif

private:
    std::unordered_map<K, V, Hash> m_map;
    mutable std::shared_mutex m_mtx;
};

} //threads

#include "threads_concurrent_hash_table.hxx"

#endif // CONCURRENT_HASH_TABLE_HPP



