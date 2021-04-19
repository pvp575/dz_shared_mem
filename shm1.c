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
    int md, fd, flag;
    int i = 0;
    key_t key;
    if ((key = ftok("./shm1.c", 0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((md = shmget(key, 10000, 0777 | IPC_CREAT | IPC_EXCL)) < 0){
        if (errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
    }
    if ((md = shmget(key, 10000, 0)) < 0){
        printf("Can\'t find shared memory\n");
        exit(-1);
    }
    if ((ptr = (int *)shmat(md, NULL, 0)) == (int *)(-1)){
        printf("Can\'t attach shared memory\n");
        exit(-1);
    }
    fd = open("./shm1.c", O_RDONLY);
    while ((flag = read(fd, &ptr[i], 1)) > 0){
        i++;
    }
    ptr[i + 1] = EOF;
    if (flag < 0){
        printf("Can\'t read the file\n");
        exit(1);
    }
    if (shmdt(ptr) < 0){
        printf("Can\'t detach shared memory\n");
        exit(-1);
    }
    printf("Writing is done\n");
    return 0;
}