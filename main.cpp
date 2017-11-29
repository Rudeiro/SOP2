#include<pthread.h>
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
using namespace std;
volatile int zwierz;
volatile int jedzenie;
volatile int dezerter;
volatile int dezerter2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* polowanie(void* arg)
{
    int sl = rand()%6 + 1;
    int sz = rand()%6 + 1;
    if(sl > sz)
    {
        zwierz += 1;
    }
    pthread_mutex_lock(&mutex);
    if(jedzenie != 0)
    {
        jedzenie -= 1;
    }
    else dezerter += 1;
    pthread_mutex_unlock(&mutex);
}
void* pieczenie(void* arg)
{

    pthread_mutex_lock(&mutex);
    if(zwierz != 0)
    {
        zwierz -= 1;
        int jedzonko = rand()%6 + 1;
        jedzenie += jedzonko;
    }
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&mutex);
    if(jedzenie != 0)
    {
        jedzenie -= 1;
    }
    else dezerter2 += 1;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    pthread_t lowca, kucharz;
    vector<pthread_t> lowcy;
    vector<pthread_t> kucharze;

    for(int i = 0; i < atoi(argv[1]); i++) lowcy.push_back(lowca);
    for(int i = 0; i < atoi(argv[2]); i++) kucharze.push_back(kucharz);
    zwierz = atoi(argv[3]);
    int l = atoi(argv[1]);

    jedzenie = atoi(argv[4]);


    for(int i = 0; i < 10; i++)
    {
        int k = l - dezerter;
        int c = atoi(argv[2]) - dezerter2;

        for(int j = 0; j < k; j++) pthread_create(&lowcy[j], NULL, polowanie, NULL);
        for(int j = 0; j < c; j++) pthread_create(&kucharze[j], NULL, pieczenie, NULL);

        for(int j = 0; j < c; j++) pthread_join(kucharze[j], NULL);
        for(int j = 0; j < k; j++) pthread_join(lowcy[j], NULL);

        cout << l - dezerter << " " << atoi(argv[2]) - dezerter2 << " ";
        cout << zwierz << " " << jedzenie <<"\n";
    }


    return 0;
}
