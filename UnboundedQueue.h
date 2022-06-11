//
// Created by dan on 10/06/2022.
//

#ifndef EX3_UNBOUNDEDQUEUE_H
#define EX3_UNBOUNDEDQUEUE_H


#include "string"
#include "queue"
#include "Semaphore.h"

using namespace std;

class UnboundedQueue : queue<string> {
private:
    Semaphore full;
    mutex m;
public:
    UnboundedQueue() : full(0) {};
    void enqueue(const string& x);
    string dequeue();
    string top();
    ~UnboundedQueue(){
        delete(this);
    }
};


#endif //EX3_UNBOUNDEDQUEUE_H
