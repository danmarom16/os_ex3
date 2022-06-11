#include <iostream>
#include "BoundedQueue.h"
#include "UnboundedQueue.h"
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
#define DEFAULT_COLOR "\033[0m"
#define YELLOW_COLOR "\033[33m"
#define FILENAME "/home/dan/CLionProjects/ex3/config.txt"

vector<BoundedQueue*> bq_arr;
UnboundedQueue* nubq = new UnboundedQueue();
UnboundedQueue* subq = new UnboundedQueue();
UnboundedQueue* wubq = new UnboundedQueue();
BoundedQueue* big_fucker_queue;


void produce(int i, int num){
    int idx;
    string types[] = {"SPORTS", "NEWS", "WEATHER"};
    int type_counter[] = {0, 0, 0};
    int j = 0;
    while(j < num){
        idx = rand() % 2;
        string x = "Producer " + to_string(i) + " " + types[idx] + " " + to_string(type_counter[idx]);
        type_counter[idx]++;
        bq_arr[i]->enqueue(x);
        //cout << GREEN_COLOR << "Producer number " + to_string(i+1) +  " insert news number " + to_string(j+1) + "\n" << DEFAULT_COLOR;
        j++;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    bq_arr[i]->enqueue(to_string(-1));
    cout << YELLOW_COLOR << "Thread " + to_string(i+1) + " finished\n" <<  DEFAULT_COLOR;
}

string get_type (const string& x){
    int counter = 0;
    int i = 0;
    int len = x.length();
    for(; i < len; i++){
        if(x[i] == ' '){
            counter++;
        }
        if(counter == 2){
            break;
        }
    }
    string temp = "";
    i++;
    while(x[i] != ' '){
        temp += x[i];
        i++;
    }
    return temp;
}

void consume(const string& x){
    string type = get_type(x);
    if(type == "SPORTS"){
      subq->enqueue(x);
    }
    else if(type == "NEWS"){
        nubq->enqueue(x);
    }
    else if(type == "WEATHER"){
        nubq->enqueue(x);
    }
    else{
        cout << "ERROR\n";
    }
}


void dispatch(int n){
    string str;
    int counter = 0;
    int i;
    while(counter != n){
        i = 0;
        counter = 0;
        while(i < n) {
            str = bq_arr[i]->dequeue();
            if(str != "-1"){
                consume(str);
            } else{
                //cout << RED_COLOR << "Producer number: " + to_string(i+1) + " raised counter\n" << endl << DEFAULT_COLOR;
                counter++;
                bq_arr[i]->enqueue(to_string(-1));
            }
            i++;
        }
    }
    //cout <<RED_COLOR << "Dispatcher " + to_string(i+1) + " inserted -1" << endl << DEFAULT_COLOR;
    subq->enqueue(to_string(-1));
    nubq->enqueue(to_string(-1));
    wubq->enqueue(to_string(-1));
    cout << YELLOW_COLOR << "Dispatcher thread is done"  << endl << DEFAULT_COLOR;

}

void co_edition(UnboundedQueue* ubq){
    int flag = 0;
    string x;
    while (flag == 0){
        this_thread::sleep_for(chrono::milliseconds(100));
        x = ubq->dequeue();
        //cout << RED_COLOR << "Its the co-editor, I consumed: \"" << x + "\""<<endl << DEFAULT_COLOR;
        if(x == "-1"){
            flag = 1;
        }
        else{
            big_fucker_queue->enqueue(x);
        }
    }
    big_fucker_queue->enqueue(to_string(-1));
    cout << YELLOW_COLOR << "Co-editor thread is done"  << endl << DEFAULT_COLOR;
}

void manage(){
    int counter = 0;
    string x;
    while(counter != 3){
        x = big_fucker_queue->dequeue();
        if(x == "-1"){
            counter++;
        }
        else{
            cout << x << endl;
        }
    }
    cout << YELLOW_COLOR << "BIG BALLS DANNY thread is done"  << endl << DEFAULT_COLOR;
}

int getData(vector<int> &sizes, vector<int> &num_products, int &fucker_size){
    int flag = 0;
    int num_of_prod = 0;
    string line, temp;
    ifstream file(FILENAME);
    if (file.is_open()) { // line.c_str()
        while (flag != 1){
            getline(file, line);    // read prod number OR Co-Editor queue size.
            temp = line;
            if(!getline(file, line))    // read num of products.
                flag = 1;
            else{
                num_products.push_back(stoi(line));
                getline(file, line);    // read queue size.
                sizes.push_back(stoi(line));
                getline(file, line);  // read empty new line
                num_of_prod++;
            }
        }
        file.close();
    }
    fucker_size = stoi(temp);
    return num_of_prod;
}

int main() {

    int fucker_size;
    vector<int> sizes;
    vector<int> num_products;
    int n = getData(sizes, num_products, fucker_size);
    thread threads_arr[n];
    big_fucker_queue = new BoundedQueue(fucker_size);

    for(int i = 0; i < n; i++){
        bq_arr.push_back(new BoundedQueue(sizes[i]));
    }
    for(int i = 0; i < n; i++){
        threads_arr[i] = thread(produce, i, num_products[i]);
    }

    thread dispatcher(dispatch, n);
    thread news_co_editor(co_edition, nubq);
    thread sport_co_editor(co_edition, subq);
    thread weather_co_editor(co_edition, wubq);
    thread screen_manager(manage);


    for(int i = 0; i < n; i++){
        threads_arr[i].join();
    }

    dispatcher.join();
    news_co_editor.join();
    sport_co_editor.join();
    weather_co_editor.join();
    screen_manager.join();

    return 0;
}


