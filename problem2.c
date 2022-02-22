#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

int size=5;// the size of the array threads 

int nums[5]={1,2,3,4,5}; // the numbers in the matirx to we will use it in the validation process

int latinSqure[5][5]={{1,2,3,4,5}, //the valide latin squre
                      {2,1,4,5,3},
                      {4,3,5,1,2},
                      {3,5,1,2,4},
                      {5,4,2,3,1} };

int valid=0; // counter to check if the number valid or not ,if it =10 then it's valid else not valid

void *Rcheck(void* i) { // row checker

int l=*(int*)i; // casting the varible from row thread creater

for(int j=0;j<size;j++){ // for to check every column in this row in the latinSqure matrix 

if(latinSqure[l][j]==nums[l]){ // if number nums[l] is unique in every column 
  valid++; // then increamnt 
}



}

 pthread_exit(0); // thread termination 

}

void *Ccheck(void*j) { // column cheker 



int u=*(int*)j;// casting the varible from column thread creater

for(int i=0;i<size;i++){  // for to check every row in this column in the latinSqure matrix 


  if(latinSqure[i][u]==nums[u]) // if number nums[u] is unique in every row
       valid=valid+1;    // then increamnt 

}



pthread_exit(0); // thread termination 

}

int main ( ) {

pthread_t threads[size];// array of threads 


int pid=fork(); // save the value of the fork

if(pid==0){ // if it's the child

latinSqure[0][4]=4; //then change the latinSqure matrix to be invalid

}


else{ // if parent
wait(NULL);// then wait for the child to terminat

}


for(int i=0;i< size;i++){// creat multithread for  the row 

pthread_create (&threads[i], NULL, Rcheck,&i) ;// give the thread id's and send it to the Rcheck with varible i
pthread_join(threads[i],NULL); //waiting the threads[i] to finish
}

for(int j=0;j< size;j++){ //creat multithread for  the row 

pthread_create (&threads[j], NULL, Ccheck,&j) ; // give the thread id's and send it to the Ccheck with varible j
pthread_join(threads[j],NULL); //waiting the threads[j] to finish
}

if(valid==10 ){ //after checking all the columns and rows we will get 10 unique elements

printf("\nvalid "); //print the resualt 

printf("The process id= %d \n",getpid()); //print the parent process and it's id
}
else{ // if it's less then 10 or greater then 10 

printf("\ninvalid "); // then it's invalid

printf("The process id  = %d",getpid()); //print the child process and it's id
}

return 0;
}

