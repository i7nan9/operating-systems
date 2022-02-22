#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_mutex_t N_mutex; //initialize the mutex locks
pthread_t Median; //thread to calculate the median
pthread_t Mean;// thread to calculate the mean
pthread_t Prime; //thread to determine the prime numbers
 int count; // The number of numbers to be used in the calculations
int nums[11]; // array of the numbers

void*median(){// meadin calculating function 

pthread_mutex_lock(&N_mutex);// locking the shared Variables

int numOfElm =count; 

if(numOfElm%2==0){// in case that the number of the numbers is even 
int a=numOfElm/2; //then select the middle index.
int d=a+1; // and the next index.

int median =(((nums[a]+nums[d])/2)); //sum the two number and divide them by 2
if(nums[a]%2!=0||nums[d]%2!=0){ // if one of the two is even 
median++; //then the median is the sum of them divide by 2 plus one
printf("median=%d\n",median); //print the median result
}


else{// else neither of the two numbers is even
printf("median=%d\n",median);} //then just print the result

}
else{ //in case that the number of the numbers is odd
int b=(numOfElm+1)/2; // then the median index is the number of the numbers plus one divide by 2
int median=((nums[b])); // determine the median number

printf("median=%d \n",median);//print the result
}

pthread_mutex_unlock(&N_mutex); // releasing the lock from the shared variables
return(NULL);

}
 
void* mean(){// mean calculating funcation

pthread_mutex_lock(&N_mutex);//locking the shared Variables

int sum=0; // sum varible to sum all the numbers
for(int i=1;i<count+1;i++){//loop to sum all the numbers in the nums array
sum=sum+nums[i];
}


double mean=sum/count;//divide the sum all of the numbers by the number of the numbers

printf(" mean=%f\n ",mean);// print the result


pthread_mutex_unlock(&N_mutex);//releasing the lock from the shared variables
return(NULL);


}


void*prime(){// prime determining funcation

pthread_mutex_lock(&N_mutex);//locking the shared variables
printf("prime numbers is ");

for(int i=1;i<count+1;i++){// loop that Pass all the numbers

if((nums[i]%2)!=0){//if the number is only divisible by itself
printf(", %d",nums[i]);//then it's prime number
}

}

printf("\n");

pthread_mutex_unlock(&N_mutex);//releasing the lock from the shared variables
return(NULL);

}

int main(int argc, char *argv[]){
if(argc<1){// if there is no numbers from the command line
exit(1); //then you can't continue the code
}

count=argc-1;// The number of digits entered from the command line minus the first element which is zero

for(int i=1;i<argc;i++){// loop to casing the number entered from the command line to integer
nums[i]= atoi(argv[i]); //saving the casing numbers in new array to use in the calculations
}

pthread_create(&Median,NULL,median,NULL);// give the Median thread id and send it to median funcation
pthread_join(Median,NULL);//wait to Median thread to finish

pthread_create(&Mean,NULL,mean,NULL);//give the Mean thread id and send it to mean funcation
pthread_join(Mean,NULL);//wait to Mean thread to finish

pthread_create(&Prime,NULL,prime,NULL);//give the Prime thread id and send it to prime funcation
pthread_join(Prime,NULL);//wait to Prime thread to finish


}