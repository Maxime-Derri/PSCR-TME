#include "Barrier.h"
#include <mutex>

pr::Barrier::Barrier(int n_): n(n_), compteur(0) {}

void pr::Barrier::waitFor() {
    std::unique_lock<std::mutex> lg(m);
    while(compteur < n)
        cv.wait(lg);
}

void pr::Barrier::done() {
    std::unique_lock<std::mutex> lg(m);
    ++compteur;
    if(compteur == n)
        cv.notify_all();
}