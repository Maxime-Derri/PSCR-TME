#pragma once

//NOTE: on écrit les constructeurs dans les .h ou dans les .c comme en C ?
//comment separer en .cpp .h avec template

#include <vector>
#include <forward_list>
#include <functional>
#include <iostream>
#include <utility>
#include <iterator>

template<typename K, typename V>
class HashMap {
    private:
        //TME2
        class Entry {
            public:
                const K key;
                V value;

                Entry(const K k, V v): key(k), value(v) {}

                bool operator==(Entry test) {
                    return this.K == test.K && this.V == test.V;
                }
        };

        typedef std::vector<std::forward_list<Entry>> buckets_t;

        //TME3
        // 4)

        class Iterator_hm { //TODO comment instancier un objet sans passer par begin() ?
            private:
                buckets_t buckets;
                typename std::vector<std::forward_list<HashMap<K, V>::Entry>>::iterator vit;
                typename std::forward_list<HashMap<K, V>::Entry>::iterator lit;

            public:
                Iterator_hm(HashMap<K, V> &map): buckets(map.buckets), vit(buckets.begin()), lit(vit->begin()) {
                    if(lit == vit->end())
                        ++(*this);
                }

                Iterator_hm &operator++() {
                    ++lit;
                    if(lit != vit->end())
                        return *this;
                    else {
                        auto end = buckets.end();
                        ++vit;
                        for(; vit!=end; ++vit) {
                            lit = vit->begin();
                            if(lit != vit->end())
                                return *this;
                        }
                    }
                    return *this; //buckets.end();
                }

                bool operator!=(Iterator_hm &other) {
                    return (this->vit != other.vit && this->lit != other.lit);
                }
                
                Entry &operator*() {
                    return *lit;
                }

                Iterator_hm &end() {
                    while(++(this->vit) != this->buckets.end()) {}
                    --(this->vit);
                    while(++(this->lit) != this->vit->end()) {}
                    return *this;
                }

        };

        
        //TME2
        buckets_t buckets;

    public:
        HashMap(const std::size_t init=100) {
            buckets.reserve(init);
            for(std::size_t i = 0; i < init; i++) {
                std::forward_list<Entry> l;
                buckets.push_back(l);
            }
        }

        V *get(const K &key) {
            std::size_t sz = buckets.size();
            std::size_t n = std::hash<K>()(key) % sz;
            auto &tmp = buckets[n];

            for(typename std::forward_list<Entry>::iterator it = tmp.begin(), end = tmp.end(); it!=end; ++it) {
                if(it->key == key)
                    return &(it->value);
            }
            return nullptr;
        }

        bool put(const K &key, const V &value) {
            std::size_t sz = buckets.size();
            std::size_t n = std::hash<K>()(key) % sz;
            //choix 1) par copie
            //auto tmp = buckets[n];

            //choix 2) par reference
            auto &tmp = buckets[n];

            for(auto it=tmp.begin(), end=tmp.end(); it!=end; ++it) {
                if(it->key == key) {
                    it->value = value;
                    return true;
                }
            }

            Entry e(key,value);
            tmp.push_front(e);
            //choix 1)
            buckets[n] = tmp; //ne pas oublier: copie (en haut)
            return false;
        }

        std::size_t size() const {
            return buckets.size();
        }

        void print_entry(const std::string word) const {
            V *val = get(word);

            if(val==nullptr)
                std::cout << word << ": " << "Not found in map." << std::endl;
            else
                std::cout << word << ": " << *val << std::endl;
        }

        std::vector<std::pair<std::string,int>> f7_tme2() const {
            std::vector<std::pair<std::string,int>> cpy;
            cpy.reserve(buckets.size());
            
            for(auto i_it=buckets.begin(), i_end=buckets.end(); i_it!=i_end; ++i_it) {
                for(auto j_it=i_it->begin(), j_end=i_it->end(); j_it!=j_end; ++j_it) {
                    cpy.push_back(std::pair(j_it->key,j_it->value));
                }
            }
            return cpy;
        }


        //TME 3

        std::vector<std::forward_list<HashMap<K, V>::Entry>> &get_buckets() {
            return buckets;
        }

        Iterator_hm begin() {
            return Iterator_hm(*this);
        }

        Iterator_hm end() {
            Iterator_hm tmp(*this);
            return tmp.end();
            
        }

};