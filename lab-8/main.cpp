#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits.h>
#include <cmath>
#include <random>
#include <x86intrin.h>

using namespace std;

void goForward(unsigned int *array, unsigned int n){
    for(unsigned int i = 0; i < n - 1; i++){
        array[i] = i + 1;
    }
    array[n - 1] = 0;
}

void goBackwards(unsigned int *array, unsigned int n){
    for(unsigned int i = n - 1; i > 0; --i)
        array[i] = i - 1;
    array[0] = n - 1;
}

void goRandom(unsigned int *array, const unsigned int arraySize) {
    auto *indexes = new unsigned int[arraySize];
    for (unsigned int i = 0; i < arraySize; ++i) {
        indexes[i] = i;
    }
    srand(time(NULL));
    for (long long i = arraySize - 1; i >= 0; --i) {
        unsigned int j = 0;
        if (i > 0) {
            j = rand() % i;
        }
        swap(indexes[i], indexes[j]);
    }

    for (unsigned int i = 0; i < arraySize - 1; ++i) {
        array[indexes[i]] = indexes[i + 1];
    }
    array[indexes[arraySize - 1]] = indexes[0];

    delete[] indexes;
}


void run(const unsigned int *array, unsigned  int n, unsigned  int k)
{
    int m = 0;
    for(unsigned int j = 0; j < n * k; ++j)
        m = array[m];
}

int main(){
    ofstream ticks;
    ofstream mem;
    ofstream log;
    log.open("/home/nextples/CLionProjects/EVM-lab8/log.txt");
    mem.open("/home/nextples/CLionProjects/EVM-lab8/mem.txt");
    ticks.open("/home/nextples/CLionProjects/EVM-lab8/ticks.txt");

    unsigned int minSize = 256;     //1 Kb
    unsigned int k = 10;
    int maxSize = 8 * 1024 * 1024 * 2;  //64 Mb

    unsigned int currentSize = minSize;

    unsigned int *array;




    currentSize = minSize;


    for (; currentSize < maxSize; currentSize = (unsigned int)(currentSize * 1.3)){
        array = (unsigned int *)malloc(currentSize * sizeof(unsigned int));
        goForward(array, currentSize);

        unsigned long long minTime = ULLONG_MAX;
        run(array, currentSize, 3);
        for (int j = 0; j < 3; j++) {
            unsigned long long start = __rdtsc();
            run(array, currentSize, k);
            unsigned long long end = __rdtsc();
//            size_t end = clock();
            size_t Time = end - start;
            if (Time < minTime) {
                minTime = Time;
            }
        }

        mem << currentSize * 32 / 8 / 1024 << endl;
        ticks << minTime / (k * currentSize) << endl;

        log << "Forward lookup for " << currentSize * 32 / 8 / 1024
            << " Kb, taken: " << minTime / (k * currentSize) << endl;

        cout << "Forward lookup for " << currentSize * 32 / 8 / 1024
             << " Kb, taken: " << minTime / (k * currentSize) << endl;
        free(array);
    }
    mem << "\n\n\n\n" << endl;
    ticks << "\n\n\n\n" << endl;

    currentSize = minSize;

    for (; currentSize < maxSize; currentSize = (unsigned int)(currentSize * 1.3)){
        array = (unsigned int *)malloc(currentSize * sizeof(unsigned int));
        goBackwards(array, currentSize);

        unsigned long long minTime = LLONG_MAX;
        run(array, currentSize, 3);
        for (int j = 0; j < 3; j++) {

            unsigned long long start = __rdtsc();
            run(array, currentSize, k);
            unsigned long long end = __rdtsc();
            unsigned long long Time = end - start;
            if (Time < minTime) {
                minTime = Time;
            }
        }

        mem << currentSize * 32 / 8 / 1024 << endl;
        ticks << minTime / (k * currentSize) << endl;

        log << "Backwards lookup for " << currentSize * 32 / 8 / 1024
            << " Kb, taken: " << minTime / (k * currentSize) << endl;

        cout << "Backwards lookup for " << currentSize * 32 / 8 / 1024
             << " Kb, taken: " << minTime / (k * currentSize) << endl;
        free(array);
    }
    mem << "\n\n\n\n" << endl;
    ticks << "\n\n\n\n" << endl;

    currentSize = minSize;


    for (; currentSize < maxSize; currentSize = (unsigned int)(currentSize * 1.3)){
        array = (unsigned int *)malloc(currentSize * sizeof(unsigned int));
        goRandom(array, currentSize);

        unsigned long long minTime = LLONG_MAX;
        run(array, currentSize, 3);
        for (int j = 0; j < 3; j++) {

            unsigned long long start = __rdtsc();
            run(array, currentSize, k);
            unsigned long long end = __rdtsc();
            unsigned long long Time = end - start;
            if (Time < minTime) {
                minTime = Time;
            }
        }
        mem << currentSize * 32 / 8 / 1024 << endl;
        ticks << minTime / (k * currentSize) << endl;

        log << "Random lookup for " << currentSize * 32 / 8 / 1024
            << " Kb, taken: " << minTime / (k * currentSize) << endl;
        cout << "Random lookup for " << currentSize * 32 / 8 / 1024
             << " Kb, taken: " << minTime / (k * currentSize) << endl;
        free(array);
    }

    mem << "\n\n\n\n" << endl;
    ticks << "\n\n\n\n" << endl;

    log.close();
    return 0;
}

