#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#define _GNU_SOURCE

void ClusterFinder(int StartCluster, int StartOfFat, int file);

int main(){

    typedef struct __attribute__((__packed__)) {
    uint8_t BS_jmpBoot[ 3 ]; // x86 jump instr. to boot code
    uint8_t BS_OEMName[ 8 ]; // What created the filesystem
    uint16_t BPB_BytsPerSec; // Bytes per Sector
    uint8_t BPB_SecPerClus; // Sectors per Cluster
    uint16_t BPB_RsvdSecCnt; // Reserved Sector Count
    uint8_t BPB_NumFATs; // Number of copies of FAT
    uint16_t BPB_RootEntCnt; // FAT12/FAT16: size of root DIR
    uint16_t BPB_TotSec16; // Sectors, may be 0, see below
    uint8_t BPB_Media; // Media type, e.g. fixed
    uint16_t BPB_FATSz16;// Sectors in FAT (FAT12 or FAT16)
    uint16_t BPB_SecPerTrk;// Sectors per Track
    uint16_t BPB_NumHeads;// Number of heads in disk
    uint32_t BPB_HiddSec;// Hidden Sector count
    uint32_t BPB_TotSec32;// Sectors if BPB_TotSec16 == 0
    uint8_t BS_DrvNum;// 0 = floppy, 0x80 = hard disk
    uint8_t BS_Reserved1;//
    uint8_t BS_BootSig;// Should = 0x29
    uint32_t BS_VolID; // 'Unique' ID for volume
    uint8_t BS_VolLab[ 11 ];// Non zero terminated string
    uint8_t BS_FilSysType[ 8 ]; // e.g. 'FAT16' (Not 0 term.)
} BootSector;

    
    char booter[sizeof(BootSector)];


    int file, byteCount = 2;

    if((file = open("fat16.img", O_RDONLY)) == -1){
        printf("File Failed to open\n");
        exit(0);
    } 
    else{
        printf("File Succesfully opened!");
        
    }

    int BootSize = sizeof(BootSector);

    read(file, booter, (sizeof(BootSector)));
    BootSector* Boot = (BootSector*)booter;


    int ReservedJump = Boot->BPB_RsvdSecCnt * Boot->BPB_BytsPerSec;
    uint16_t NextClust;
    
   
    //lseek(file, ReservedJump, SEEK_SET);   // seek ahead past the Reserved Sectors
    
    ClusterFinder(6, ReservedJump, file);
    //Tester(ReservedJump, file, BootSize);

       
       
       
       
        //uint16_t* buffer = malloc(sizeof(uint16_t));

       // if((read(file, buffer, (7*(sizeof(uint16_t))))) == -1){
      //  printf("ERROR: Unable to read file");
      //  }
        //printf(" %u\n", *buffer);
      //  NextClust = (uint16_t) *buffer;
      //  printf("%u\n", NextClust);
//
       // if(*buffer >= 0xfff8){
       //     printf("END");
      //  }
      //  free(buffer);
        
    
    




    // boot sector info
    /**
     * RsvdSecCnt = 4
     * BytsPerSec = 512
     * SecPerClus = 4
     * TotSec16 = 32000
     * NumFATs = 2
    */




    close(file);   




   
    
}




    void ClusterFinder(int StartCluster, int StartOfFat, int file){
        int Done = 0;
        int NextClust;
        uint16_t* reader = malloc(sizeof(uint16_t));
        lseek(file, (StartOfFat + (StartCluster * sizeof(uint16_t))), SEEK_SET);
        read(file, reader, sizeof(uint16_t));
        printf("Start: %u\n", *reader);
        //free(reader);
    
        while(Done == 0){
            NextClust = (*reader * sizeof(uint16_t));
            memset(reader, NULL, 2);
            lseek(file, (StartOfFat + NextClust), SEEK_SET);
            read(file, reader, sizeof(uint16_t));
            if(*reader >= 0xfff8 || *reader == 0){
                Done = 1;
                printf("EOF");
            }
            else{
                printf("%u\n", *reader);
            }
        }


    }

    void Tester(int FatStart, int file, int BootSize){
        uint16_t* reader = malloc(sizeof(uint16_t));
        int JumpAmount = BootSize + FatStart;
        lseek(file, JumpAmount, SEEK_SET);
        read(file, reader, sizeof(uint16_t));
        printf("%u\n", *reader);
        }



 char* Reader(int file, char * buffer, int count ){
        if((read(file, buffer, count)) == -1){
        printf("ERROR: Unable to read file");
        return NULL;
    }

    else{
            return buffer;
       
    }

    }