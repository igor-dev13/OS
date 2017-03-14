#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

int iterationsNumber = 10000;
int counter = 0;

void * thread_func1()
{
    int i;
    int counter1 = 0;

    for (i = 0; counter < iterationsNumber; i++) {
        pthread_mutex_lock( &mutex1 );
        counter++;
        pthread_mutex_unlock( &mutex1 );
        counter1 ++;
    }

     printf("common counter is %d\n", counter);
     printf("pthread counter1 is %d\n", counter1);
}
void * thread_func2()
{
    int i;
    int counter2 = 0;

    for (i = 0; counter < iterationsNumber; i++) {
        pthread_mutex_lock( &mutex1 );
        counter++;
        pthread_mutex_unlock( &mutex1 );
        counter2++;
    }

    printf("pthread counter2 is %d\n", counter2);
}
int main(int argc, char * argv[])
{
    int result;
    pthread_t thread1, thread2;

    result = pthread_create(&thread1, NULL, thread_func1, NULL);

    if (result != 0) {
        perror("Creating the first thread");
        return EXIT_FAILURE;
    }

    result = pthread_create(&thread2, NULL, thread_func2, NULL);

    if (result != 0) {
        perror("Creating the second thread");
        return EXIT_FAILURE;
    }

    result = pthread_join(thread1, NULL);

    if (result != 0) {
        perror("Joining the first thread");
        return EXIT_FAILURE;
    }

    result = pthread_join(thread2, NULL);

    if (result != 0) {
        perror("Joining the second thread");
        return EXIT_FAILURE;
    }

    printf("Done\n");
    return EXIT_SUCCESS;
}
