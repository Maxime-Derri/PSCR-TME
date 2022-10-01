#pragma once

//NOTE: on écrit les constructeurs dans les .h ou dans les .c comme en C ?
//comment separer en .cpp .h avec template

#include <vector>
#include <forward_list>
#include <functional>
#include <iostream>
#include <utility>

template<typename K, typename V>
class HashMap {
    class Entry {
        public:
            const K key;
            V value;
            Entry(const K k, V v): key(k), value(v) {}
    };
    
    typename std::vector<std::forward_list<Entry>> buckets_t;
    
    public:
        HashMap(std::size_t init=100) {
            buckets_t.reserve(init);
            for(std::size_t i = 0; i < init; i++) {
                std::forward_list<Entry> l;
                buckets_t.push_back(l);
            }
        }

        V *get(const K &key) const {
            std::size_t sz = buckets_t.size();
            std::size_t n = std::hash<K>()(key) % sz;
            auto tmp = buckets_t[n];

            for(typename std::forward_list<Entry>::iterator it = tmp.begin(), end = tmp.end(); it!=end; ++it) {
                if(it->key == key)
                    return &(it->value);
            }
            return nullptr;
        }

        bool put(const K &key, const V &value) {
            std::size_t sz = buckets_t.size();
            std::size_t n = std::hash<K>()(key) % sz;
            //choix 1) par copie
            //auto tmp = buckets_t[n];

            //choix 2) par reference
            auto &tmp = buckets_t[n];

            for(auto it=tmp.begin(), end=tmp.end(); it!=end; ++it) {
                if(it->key == key) {
                    it->value = value;
                    return true;
                }
            }

            Entry e(key,value);
            tmp.push_front(e);
            //choix 1)
            buckets_t[n] = tmp; //ne pas oublier: copie (en haut)
            return false;
        }

        std::size_t size() const {
            return buckets_t.size();
        }

        void print_entry(const std::string word) const {
            V *val = get(word);

            if(val==nullptr)
                std::cout << word << ": " << "Not found in map." << std::endl;
            else
                std::cout << word << ": " << *val << std::endl;
        }

        std::vector<std::pair<std::string,int>> f7() const {
            std::vector<std::pair<std::string,int>> cpy;
            cpy.reserve(buckets_t.size());
            
            for(auto i_it=buckets_t.begin(), i_end=buckets_t.end(); i_it!=i_end; ++i_it) {
                for(auto j_it=i_it->begin(), j_end=i_it->end(); j_it!=j_end; ++j_it) {
                    cpy.push_back(std::pair(j_it->key,j_it->value));
                }
            }
            return cpy;
        }

        void f8(std::vector<std::pair<std::string,int>> &vec) const {
	        std::sort(vec.begin(), vec.end(), [](const auto &p1, const auto &p2) {
		        return p1.second > p2.second;
	        });

	        for(auto it=vec.begin(), end=vec.begin()+10; it!= end; ++it) {
                std::cout << it->first << ": " << it->second << std::endl;
	        }
        }

};