#include "Pool.h"
#include "Queue.h"
#include "Job.h"

pr::Pool::Pool(int qsize): queue(qsize)  {}

void pr::poolWorker(Queue<Job> &queue) {
    while(true) {
        Job *j = queue.pop();
        if(j==nullptr)
            break;
        j->run();
        delete j;
    }
}

void pr::Pool::start(int nbthread) {
    for(int i = 0; i < nbthread; ++i) {
        threads.emplace_back(poolWorker, std::ref(queue));
    }
}

void pr::Pool::stop() {
    queue.set_blocking(false);
    for(auto &t : threads)
        t.join();
}

void pr::Pool::submit(Job * job) {
    queue.push(job);
}