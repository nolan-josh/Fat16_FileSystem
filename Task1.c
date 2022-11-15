#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>



int main(){

    
    char buffer[1];   // buffer array for the text scanned to be stored in

    FILE *filehandle;    // create a filehandler and check its not empty
    filehandle = fopen("fat16.img", "r");   // maybe rb instead of r but not sure
    if(filehandle == NULL){
        printf("ERROR: FILE IS NULL");
    }
    
    int startPos = 0; // start pos for offset
    int currentPos; 
    int CharCounter = 0;
    int limit = 4000;
    
    fseek(filehandle, 5000000, startPos);  // seek / skips to a number of bytes into the file from start pos // skip 5million in since its a huge fi;e

    fread(buffer, sizeof(char), 1, filehandle);
    while(buffer != NULL && buffer != "/0"){
        printf("%s", buffer);
        fread(buffer, sizeof(char), 1, filehandle);  // read the size of a character 5 times and store in buffe
        if(CharCounter == limit){  // number of characters into it it will break at 
           // exit(1);
             break;
        }
        CharCounter++;
    }


    // maybe put iff statement in while play around since its getting to the first null pointer after the first tiny file
    // and then ending
    
    fclose(filehandle);

}