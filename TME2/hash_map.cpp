#include <vector>
#include <forward_list>
#include <functional>
#include <iostream>

#include "hash_map.h"


int main(int argc, char *argv[]) {
    HashMap<int, std::string> test;
    bool t1 = test.put(18, "jean");
    bool t3 = test.put(537, "changrui");

    std::cout << t1 << ": " << *(test.get(18)) << std::endl;
    std::cout << t3 << ": " << *(test.get(537)) << std::endl;

    bool t2 = test.put(18, "paul"); //changement val
    std::cout << t2 << ": " << *(test.get(18)) << std::endl;
    return 0;
}