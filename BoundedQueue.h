//
// Created by dan on 10/06/2022.
//

#ifndef EX3_BOUNDEDQUEUE_H
#define EX3_BOUNDEDQUEUE_H

#include "string"
#include "queue"
#include "Semaphore.h"

using namespace std;

class BoundedQueue : queue<string> {
private:
    Semaphore full;
    Semaphore empty;
    mutex m;
public:
    BoundedQueue(int size) : empty(size), full(0){};
    void enqueue(const string& x);
    string dequeue();
    string top();
    ~BoundedQueue(){ delete(this);};
};


#endif //EX3_BOUNDEDQUEUE_H
