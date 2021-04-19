#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int *ptr;
    int md;
    key_t key;
    int i = 0;
    if ((key = ftok("./shm1.c", 0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((md = shmget(key, 10000, 0)) < 0){
        printf("Can\'t find shared memory\n");
        exit(-1);
    }
    if ((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
        printf("Can\'t attach shared memory\n");
        exit(-1);
    }
    printf("Text:\n\n");
    while (ptr[i] != EOF){
        putchar(ptr[i]);
        i++;
    }
    if (shmctl(md, IPC_RMID, NULL) < 0){
        printf("Can\'t clear shared memory\n");
        exit(-1);
    }
    printf("\nEnd of file\nReading is done\n");
    return 0;
}