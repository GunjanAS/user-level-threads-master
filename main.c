/*
*
*  Created by Saurabh Singh on 10/28/16.
*  Authors: Saurabh Singh,
*			Alok Singh
*           
*/

#include <stdio.h>
#include "my_pthread_t.h"
#include "my_mutex_and_que.h"
#include <unistd.h>
#include <sys/time.h>


my_pthread_mutex_t mutex;

/***
 * busyWait - Function to mimic sleep() as sleep() wakes on alarm
 * @param 	i 	int 	Approx. duration of wait
 * @return 	null
 */
void busyWait(int i) {
	int j = 214740000;
	i = i < 0 ? 1 : i;
	while (i>=0) {
		while (j>=0) {j--;}
		i--;
	}
}
/***
 * funThread1 - Function for thread 1. This is the function that is executed when thread 1 is scheduled.
 * @param 	null
 * @return 	null
 */
void funThread1() {
	printf("Thread  1 trying to lock the mutex now\n");
    my_pthread_mutex_lock(&mutex);
    printf("Thread  1 sucessfully locked the mutex!!\n");
    int i;
    for(i = 0; i < 10; i++){
        busyWait(1);
        printf("This is the first Thread 1\n");
     }
    my_pthread_mutex_unlock(&mutex);
    printf("Thread  1 unlocked the mutex\n");
}

/***
 * funThread2 - Function for thread 2. This is the function that is executed when thread 2 is scheduled.
 * @param 	null
 * @return 	null
 */
void funThread2() {
	printf("Thread  2 trying to lock the mutex now\n");
    my_pthread_mutex_lock(&mutex);
    printf("Thread  2 sucessfully locked the mutex!!\n");
    int i;
    for(i = 0; i < 3 ; i++) {
        busyWait(1);
        printf("This is the second Thread 2\n");
    }
    my_pthread_mutex_unlock(&mutex);
    printf("Thread  2 unlocked the mutex\n");
    printf("Thread  2 EXITING!!!!!!!!\n");
    my_pthread_exit(NULL);
}

/***
 * funThread3 - Function for thread 3. This is the function that is executed when thread 3 is scheduled.
 * @param 	null
 * @return 	null
 */
void funThread3() {
    int i;
    long j;
    for(i = 0; i < 2 ; i++) {
        busyWait(1);
        printf("This is the third Thread 3\n");
    }
    for(i = 0; i < 4 ; i++) {
		for(j=0;j<1000000000;j++){}
        my_pthread_yield();
		printf("Thread 3 YIELDED!!\n");
    }
    printf("Thread  3 is done!\n");
}
/***
 * funThread4 - Function for thread 4. This is the function that is executed when thread 4 is scheduled.
 * @param 	null
 * @return 	null
 */
void funThread4() {
	printf("Thread  4 trying to lock the mutex now\n");
    my_pthread_mutex_lock(&mutex);
    printf("Thread  4 sucessfully locked the mutex!!\n");
    int i;
    for(i = 0; i < 4 ; i++) {
        busyWait(1);
        printf("This is the fourth Thread 4\n");
    }
    my_pthread_mutex_unlock(&mutex);
    printf("Thread  4 unlocked the mutex\n");
}

int main(int argc, const char * argv[]) {
	struct timeval start, end;
	float delta;
	gettimeofday(&start, NULL);
	my_pthread_t thread1,thread2,thread3,thread4;
    my_pthread_mutex_init(&mutex);
    //Create threads
    my_pthread_create(&thread1, NULL, &funThread1,NULL);
    my_pthread_create(&thread2, NULL, &funThread2,NULL);
    my_pthread_create(&thread3, NULL, &funThread3,NULL);
    my_pthread_create(&thread4, NULL, &funThread4,NULL);
    //Call join on the threads
    my_pthread_join(&thread1,NULL);
    my_pthread_join(&thread2,NULL);
    my_pthread_join(&thread3,NULL);
    my_pthread_join(&thread4,NULL);
    //Destroying the mutex
    my_pthread_mutex_destroy(&mutex);
    gettimeofday(&end, NULL);
    delta = (((end.tv_sec  - start.tv_sec)*1000) + ((end.tv_usec - start.tv_usec)*0.001));
    printf("Execution time in Milliseconds: %f\n",delta);
    printf("Scheduler cycle counts %d\n",cycle_counter);
    printf("Ending main!\n");
    return 0;
}
