#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int pidd;
    pidd = fork();

    if(pidd == 0){
        printf("I am the child!\n");
    }
    else{
        printf("I am the parent!\n");
    }

}