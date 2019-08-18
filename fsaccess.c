#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/mount.h>

/*constants globally defined. (reference: Unix V6 file system manual)*/
const unsigned short BlOCK_SIZE = 512;
const unsigned short ISIZE = 32;
const unsigned short inode_alloc = 0100000;
const unsigned short plainFile = 000000;
const unsigned short largeFile = 010000;
const unsigned short blockType = 060000;
const unsigned short directory = 040000;
const unsigned short charType = 020000;

struct inode{
  unsigned short flags;
  char nlinks;
  char uid;
  char gid;
  char size0;
  unsigned short size1;
  unsigned short addr[8];
  unsigned short actime[2];
  unsigned short modtime[2];
};

int main(){
int option = 0;
int cont = 1;
int inodeNum = 0;
int type = 0;
struct inode node;
int fd = 0;

while(cont == 1){
printf("Enter 1 for mount filenm\n");
printf("Enter 2 for ckfiletype n\n");
printf("Enter 3 for filesize m\n");
printf("Enter 4 to save and quit\n");
scanf("%d", &option);

  switch(option){
    case 1:
    //Mount filenm
    /*
    open the file
    */
    fd = open("file.data",O_RDONLY);
    
    break;
    
    case 2:
    //Ckfiletype n
    
    /*
    take num of inode
    find bits 2 and 3
    if statements to output result
    */
    
    printf("What is the number of the inode you are looking for?\n");
    scanf("%d", &inodeNum);

    if(inodeNum == 0){
      //block 0
      lseek(fd, 0, SEEK_SET);
      read(fd, &node, sizeof(node));
      int fileType = (node.flags&(11 << 13)) >> 13;
      
      if(fileType == 3){
        printf("This is a block-type special file.\n");
      }
      else if(fileType == 2){
        printf("This is a directory file.\n");
      }
      else if(fileType == 1){
        printf("This is a character-type special file.\n");
      }
      else if(fileType == 0){
        printf("This is a plain file.\n");
      }
    }
    else if(inodeNum == 1){
      //block 1
      lseek(fd,BLOCK_SIZE, SEEK_SET);
      read(fd, &node, sizeof(node));
      
      int fileType = (node.flags&(11 << 13)) >> 13;
      
      if(fileType == 3){
        printf("This is a block-type special file.\n");
      }
      else if(fileType == 2){
        printf("This is a directory file.\n");
      }
      else if(fileType == 1){
        printf("This is a character-type special file.\n");
      }
      else if(fileType == 0){
        printf("This is a plain file.\n");
      }
    }
    
    else{
      inodeNum = inodeNum - 1;
      
      int offset = 2*512 + inodeNum*32;
      lseek(fd,offset, SEEK_SET);
      read(fd, &node, sizeof(node));
      
      int fileType = (node.flags&(11 << 13)) >> 13;
      
      if(fileType == 3){
        printf("This is a block-type special file.\n");
      }
      else if(fileType == 2){
        printf("This is a directory file.\n");
      }
      else if(fileType == 1){
        printf("This is a character-type special file.\n");
      }
      else if(fileType == 0){
        printf("This is a plain file.\n");
      }
    }
    break;
    
    case 3:
    //filesize m
    
    /*
    take num of inode
    find bit 4
    that will say if it is large or small
    then find b and i to see if it is huge or not
    */
    printf("What is the number of the inode you are looking for?\n");
    scanf("%d", &inodeNum);
    
    if(inodeNum == 0){
      //block 0
      lseek(fd,0, SEEK_SET);
      read(fd, &node, sizeof(node));
      
      int fileSize = (node.flags&(1 << 15)) >> 15;
      printf("The file size 12 is %d\n", fileSize);
    }
    else if(inodeNum == 1){
      //block 1
      lseek(fd,BLOCK_SIZE, SEEK_SET);
      read(fd, &node, sizeof(node));
      
      unsigned short leftSize = node.size0;
      unsigned short rightSize = node.size1;
      int size = leftSize+rightSize;
      
      
      printf("The file tryl is %d\n", size);
      //printf("The file size1 is %d\n", fileSize1);
    }
    
    else{
      inodeNum = inodeNum - 1;
      
      //bits 2 and 3 display the type of file
      int offset = 2*512 + inodeNum*32;
      lseek(fd,offset, SEEK_SET);
      read(fd, &node, sizeof(node));
      
      unsigned short leftSize = node.size0;
      unsigned short rightSize = node.size1;
      int size = leftSize+rightSize;
      
      
      printf("The file tryl is %d\n", size);
      //printf("The file size1 is %d\n", fileSize1);
      
    }
    
    break;
    
    case 4:
    //quit
    cont = 0;
    return 0;
    break;
    
    default:
    printf("What is the number of the inode you are looking for?\n");
    
  }//end switch
} // end while loop
}