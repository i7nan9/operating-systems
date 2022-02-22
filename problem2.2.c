#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;//initialize the semaphore

void*prepare_capsule(){ // Sara’s operation



printf("\n Sara's opration Done");//we didn't put a wait function here since sara always must start the first

sem_post(&mutex);//since the semaphore value initialize, by zero after sara finish the lock will release


}

void*make_coffee(){ //Muhammad’s operation

sem_wait(&mutex); // Muhammad must wait until sara prepar at least one capsule 

printf("\n Muhammad's opration"); //Muhammad is Done

sem_post(&mutex);// and the lock will release so Abdullah can serves the coffee


}

void*serve_coffee(){ // Abdullah’s operation

sem_wait(&mutex);// Abdullah must wait to sara and Muhammad to Done thire operations to start

printf("\n Abdullah's opration");//Abdullah is Done

sem_post(&mutex);//lock release


}

int main(){

sem_init(&mutex,0,5); // creat and initialize by zero and 5 coffee capsules as max

pthread_t Sara ,Mohammed ,Abdullah; //initialize 3 threads present Sara, Mohammed and Abdullah

pthread_create(&Sara,NULL,prepare_capsule,NULL); //give the thread id and send it to prepare_capsule funcation
pthread_join(Sara,NULL); // wait to t1 to finish

pthread_create(&Mohammed ,NULL,make_coffee,NULL); //give the thread id and send it to make_coffee funcation
pthread_join(Mohammed,NULL);//wait to t2 to finish

pthread_create(&Abdullah,NULL,serve_coffee,NULL);//give the thread id and send it to serve_coffee funcation
pthread_join(Abdullah,NULL);//wait to t3 to finish



}