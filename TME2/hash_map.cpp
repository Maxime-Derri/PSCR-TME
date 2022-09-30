#include <vector>
#include <forward_list>
#include <functional>
#include <iostream>

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

    V *get(const K &key) {
        std::size_t sz = buckets_t.size();
        std::size_t n = std::hash<K>()(key) % sz;
        auto tmp = buckets_t[n];

        for(auto it = tmp.begin(), end_ = tmp.end(); it!=end_; ++it) {
            if(it->first == key)
                std::cout << std::endl;
        }
        
    }

    std::size_t size() const {
        return buckets_t.size();
    }

};


int main() {}