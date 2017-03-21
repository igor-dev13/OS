#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#define TRUE  1
#define FALSE 0

int iterationsNumber = 100000;
int counter = 0;

int abFlags[1];
int nTurn = 1;

void * thread_func1()
{
    int i;
    int counter1 = 0;

    for (i = 0; counter < iterationsNumber; i++) {
        abFlags[0] = TRUE;

        while (abFlags[1])
            if (nTurn == 1)
            {
                abFlags[0] = FALSE;
                    while (nTurn == 1)
                        /* ожидание */;
                abFlags[0] = TRUE;
            }

        // критический раздел
        counter++;
        counter1 ++;

        nTurn = 1;
        abFlags[0] = FALSE;
    }

     printf("common counter is %d\n", counter);
     printf("pthread counter1 is %d\n", counter1);
}
void * thread_func2()
{
    int i;
    int counter2 = 0;

    for (i = 0; counter < iterationsNumber; i++) {
        abFlags[1] = TRUE;

        while (abFlags[0])
            if (nTurn == 0)
            {
                abFlags[1] = FALSE;
                    while (nTurn == 0)
                        /* ожидание */;
                abFlags[1] = TRUE;
            }

        // критический раздел

        counter++;
        counter2++;

        nTurn = 0;
        abFlags[1] = FALSE;
    }

    printf("pthread counter2 is %d\n", counter2);
}
int main(int argc, char * argv[])
{
    int result;
    pthread_t thread1, thread2;
    abFlags[0] = TRUE;
    abFlags[1] = TRUE;

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
