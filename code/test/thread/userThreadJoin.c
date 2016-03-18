#include "syscall.h"

void wait(void* arg) {
	PutString("Waiting\n");
	
	int i;
    for (i=0; i < 1000000;)
        i++;
	
	PutString("End waiting\n");
}

void joinOn_1(void* tId) {
    PutString("Join on 1 - beginning\n");
  
    UserThreadJoin(*((int*)tId));
    
    PutString("Join on 1 - ending\n");
}

void joinOn_2(void* tId) {
    PutString("Join on 2 - beginning\n");
        
    UserThreadJoin(*((int*)tId));
    
    PutString("Join on 2 - ending\n");
}

int main() {
    PutString("Beginning main\n");
    
    int tId1, tId2, tId3;

    tId1 = UserThreadCreate(wait, 0);
    tId2 = UserThreadCreate(joinOn_1, &tId1);
    tId3 = UserThreadCreate(joinOn_2, &tId2);
    
    PutString("Joining on all threads\n");
    UserThreadJoin(tId3);
    PutString("Join done\n");

    return 2;
}

