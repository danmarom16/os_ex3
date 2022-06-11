//
// Created by dan on 10/06/2022.
//

#include "BoundedQueue.h"


void BoundedQueue :: enqueue(const string& x) {
    empty.down();
    m.lock();
    push(x);
    m.unlock();
    full.up();
}

string BoundedQueue :: dequeue() {
    full.down();
    m.lock();
    string x = front();
    pop();
    m.unlock();
    empty.up();
    return x;
}

string BoundedQueue :: top(){
    return front();
}