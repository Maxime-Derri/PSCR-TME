#pragma once

//NOTE: on écrit les constructeurs dans les .h ou dans les .c comme en C ?
//comment separer en .cpp .h avec template

#include <vector>
#include <forward_list>
#include <functional>

template<typename K, typename V>
class HashMap {
    class Entry {
        const K key;
        V value;

        Entry(const K k, V v): key(k), value(v) {}
    };
    
    std::vector<std::forward_list<Entry>> buckets_t;
    
    HashMap(std::size_t init=100) {
        buckets_t.reserve(init);
        for(std::size_t i = 0; i < init; i++) {
            std::forward_list<Entry> l;
            buckets_t.push_back(l);
        }
    }

    V *get(const k &key) {
        std::size_t n = std::hash<k>()(key) % buckets_t.size();
        
    }

    std::size_t size() const {
        return buckets_t.size();
    }

};