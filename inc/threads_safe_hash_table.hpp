#ifndef SAFE_HASH_TABLE_HPP
#define SAFE_HASH_TABLE_HPP

#include <unordered_map>
#include <memory>
#include <shared_mutex>
#include <mutex>

namespace threads {

template <typename K, typename V>
class SafeHashTable {
public:
    SafeHashTable();
    SafeHashTable(SafeHashTable const& a_other) = default;
	SafeHashTable& operator=(SafeHashTable const&) = default;
	~SafeHashTable() = default;

    const V& Get(K const& a_key) const;
    size_t Count(K const& a_key) const;
    bool Containes(K const& a_key) const;
    
    void Insert(K const& a_key, V const& a_val);
    bool Erase(K const& a_key);
    bool Update(K const& a_key, V const& a_val);

    #ifdef DEBUG
        void Print() const;
		size_t GetSizeOfMutexHash() const;
	#endif

private:
    std::shared_ptr<std::shared_mutex> findOrGenerateSharedPtrToMutex(K const& a_key) const;
    void earseMutexIfNeeded(K const& a_key, std::shared_ptr<std::shared_mutex>& a_sharedPtr) const;

private:
    using SharedPtr = std::shared_ptr<std::shared_mutex>;
    using MtxMap = std::unordered_map<K, SharedPtr>;
    std::unordered_map<K,V> m_map;
    mutable std::mutex m_mtx;
    mutable MtxMap m_mtxMap;
};

} //threads

#include "threads_safe_hash_table.hxx"

#endif // SAFE_HASH_TABLE_HPP



