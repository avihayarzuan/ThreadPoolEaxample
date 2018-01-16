//============================================================================
// Name        : PoolExample.cpp
// Author      : Avihay Arzuan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Task.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using namespace std;

#define THREADS_NUM 3
#define TASKS_NUM 5

#include <pthread.h>

void* print(void *taskId);
pthread_mutex_t lock2;
//pthread_mutex_init(&lock2, NULL);

int main() {
    ThreadPool pool(THREADS_NUM);
    Task *tasks[TASKS_NUM];
    for (int i = 0; i < TASKS_NUM; i++) {
        tasks[i] = new Task(print, (void *) i);
        pool.addTask(tasks[i]);
    }
    char ch;
    cout << "Type a char to exit" << endl;
    cin >> ch;
    pool.terminate();
    for (int i = 0; i < TASKS_NUM; i++) {
        delete tasks[i];
    }
    cout << "End of main" << endl;
}

void* print(void *taskId) {
    long id = (long) taskId;
    for (int i = 1; i <= 3; i++) {
        pthread_mutex_lock(&lock2);
        cout << "Task " << id << " prints: " << i << endl;
        pthread_mutex_unlock(&lock2);
        sleep(1);
    }
    return NULL;
}
