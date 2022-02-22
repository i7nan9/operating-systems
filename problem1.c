#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


int size=5;// globel varablie for the size of the array threads 

int nums[5]={1,2,3,4,5}; //globel array for the numbers in the matirx to we will use it in the validation process

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





for(int i=0;i< size;i++){// creat multithread for  the row 

pthread_create (&threads[i], NULL, Rcheck,&i) ;// give the thread id's and send it to the Rcheck with varible i
pthread_join(threads[i],NULL); //waiting the threads[i] to finish
}

for(int j=0;j< size;j++){ //creat multithread for  the column

pthread_create (&threads[j], NULL, Ccheck,&j) ; // give the thread id's and send it to the Ccheck with varible j
pthread_join(threads[j],NULL); //waiting the threads[j] to finish
}

if(valid==10 ){ //after checking all the columns and rows we will get 10 unique elements
for(int i=0;i<size;i++){
for(int j=0;j<size;j++){
printf("%d ,",latinSqure[i][j]); // if valid=10 then print the valid squre
}
printf("\n");}

printf("\nvalid\n"); // the result of checking

}

else{ // if it's less then 10 or greater then 10 
for(int i=0;i<size;i++){
for(int j=0;j<size;j++){
printf("%d ,",latinSqure[i][j]); //then print the invalid squre
}
printf("\n");}

printf("\n invalid\n"); //  the result of checking



}

return 0;
}

