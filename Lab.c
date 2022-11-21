#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#define _GNU_SOURCE

int main(){


    __off64_t Offset = 15;
    int file, byteCount = 200;
    char buffer[200];
    if((file = open("Input.txt", O_RDONLY)) == -1){
        printf("File Failed to open\n");
        exit(0);
    } 
    else{
        printf("File Succesfully opened!");
        
    }


   // readahead(file, Offset, 200);

   lseek(file, Offset, SEEK_CUR);

    if((read(file, buffer, byteCount)) == -1){
        printf("ERROR: Unable to read file");
    }

    else{
       // buffer[byteCount] = "\0";
        
        printf("File Content: %s\n", buffer);
    }


   close(file);   // close the file

   
   // itoa(filehandle, buffer, )
    
}