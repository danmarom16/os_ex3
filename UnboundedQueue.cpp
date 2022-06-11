//
// Created by dan on 10/06/2022.
//

#include "UnboundedQueue.h"


void UnboundedQueue :: enqueue(const string& x) {
    m.lock();
    push(x);
    m.unlock();
    full.up();
}

string UnboundedQueue :: dequeue() {
    full.down();
    m.lock();
    string x = front();
    pop();
    m.unlock();
    return x;
}

string UnboundedQueue :: top(){
    return front();
}