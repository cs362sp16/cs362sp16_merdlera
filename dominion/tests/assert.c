#include <stdio.h>
#include "assert.h"

int myAssertError = 0;

void myAssertTrue(int result, const char *msg) {
    if (!result){
        printf("Assertion Failed: %s\n", msg);
        myAssertError = 1;
    }
}

void checkAsserts(){
    if (!myAssertError){
        printf("Test passed.\n");
    }
    else {
        printf("Test failed.\n");
    }
}
