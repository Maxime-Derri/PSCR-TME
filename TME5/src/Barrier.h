#pragma once

#include <mutex>
#include <condition_variable>


namespace pr {

class Barrier {
    std::mutex m;
    int n, compteur;
    std::condition_variable cv;

    public:
        Barrier(int n_);
        void waitFor();
        void done();
};

}