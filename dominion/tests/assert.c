#include <stdio.h>
#include "assert.h"

int myAssertError = 0;

void myAssertTrue(int result, const char *msg){
    if(!result){
        printf("Assertion Failed: %s\n", msg);
        myAssertError = 1;
    }
}

void checkAsserts(){
    if(!myAssertError){
        printf("Unit test passed.\n");
    }else{
        printf("Unit test failed.\n");
    }
}