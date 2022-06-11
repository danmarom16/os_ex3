//
// Created by dan on 10/06/2022.
//

#ifndef EX3_SEMAPHORE_H
#define EX3_SEMAPHORE_H
#include "mutex"
#include "semaphore.h"

class Semaphore {
private:
    sem_t sem;
public:
    int down(){ return sem_wait(&sem);};
    int up(){ return sem_post(&sem);};
    Semaphore(int size){
        sem_init(&sem, 0, size);
    }
    ~Semaphore(){
        sem_destroy(&sem);
    }

};


#endif //EX3_SEMAPHORE_H
