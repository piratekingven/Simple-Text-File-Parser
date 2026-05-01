#include<stdio.h>
#include<stdlib.h>
int global_c;
typedef struct word{
    int length;
    char *string_starting_pointer;
}word;//this struct holds each word that is read from the file

void file_given_checker();

int main(int argc, char *argv[]){
global_c=argc;
file_given_checker();
//----------------------------------------------------------------------
char *filename = argv[1];
FILE *fptr;
int x;
fptr = fopen(filename,"r");
if(fptr==NULL){printf("Error in opening the file, please check if the file exists in the same directory");return 0;}
x = fgetc(fptr);if(x==EOF){printf("It is an empty file");return 0;}else{ungetc(x,fptr);}
//----------------------------------------------------------------------
int allocated_arraysize = 20;//the size used to allocate memory to the array
int arraysize = 0;//the current number of slots filled in our array
word *array = malloc(allocated_arraysize * sizeof(word));//initial initialization of array of words done
if(array==NULL){printf("Allocation of memory failed. Exiting program");return 0;}
word *temp_array_r_pointer;//temporary pointer used to allocate memory for the array of words
//-----------------------------------------  
int character_being_read = 0;//the character currently being read by fgetc
int bool_in_word=0;
int wordlength = 0;//length of the word being read
int wordpointer= 0;//pointer for the string in the struct word
int arraypointer = 0;//pointer for the array of words
word *copyarray = array;//copies the pointer to the array so that we keep the original starting safe
char *copy_string_starting_pointer;//a copied pointer to the pointer to the string in the struct word
char *temp_r_pointer;//temporary pointer used for reallocation of the string memory
int allocated_size = 20; // the size used to allocate memory for the string in the word
//------------------------------------------
while((character_being_read=fgetc(fptr))!=EOF){//loop to read the file, stops when end of file is reached (EOF)
    //-------------------------------------------the next conditions handle not being in the word
    if(character_being_read==32&&bool_in_word==0){bool_in_word=0;wordpointer=0;wordlength=0;}//if character being read is a blankspace and we are not in a word, it just ignores and moves forward
    else if(character_being_read==10&&bool_in_word==0){bool_in_word=0;wordpointer = 0;wordlength=0;}//character read is newline char, so we are no longer in a word, it just ignores and moves forward
    //-------------------------------------------the next conditions handle the word being added
    else if(character_being_read!=32&&character_being_read!=10&&bool_in_word==0){//character being read is a valid char and is the first char of the word
        if(arraysize==allocated_arraysize){//handles the array being full
            allocated_arraysize=allocated_arraysize+20;temp_array_r_pointer=realloc(array,allocated_arraysize*sizeof(word));
            if(temp_array_r_pointer!=NULL){array=temp_array_r_pointer;}
            else{printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");arraypointer--;break;}}
        allocated_size=20;
        wordlength = 0; wordpointer = 0; 
        bool_in_word=1;
        copy_string_starting_pointer=array[arraypointer].string_starting_pointer;
        copy_string_starting_pointer=malloc(allocated_size*sizeof(char));
        if(copy_string_starting_pointer==NULL){printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");arraypointer--;break;}
        else{array[arraypointer].string_starting_pointer=copy_string_starting_pointer;copy_string_starting_pointer[wordpointer]=(char)character_being_read;wordpointer++;wordlength++;}
    }
    else if(character_being_read!=32&&character_being_read!=10&&bool_in_word==1){//character being read is a valid char and is not the first char in the word
        bool_in_word=1;
        if(wordlength==allocated_size){allocated_size=allocated_size+20;//handling wordlength reaching the default allocated size (reallocing more memory)
            temp_r_pointer=realloc(copy_string_starting_pointer,allocated_size);
            if(temp_r_pointer!=NULL){copy_string_starting_pointer=temp_r_pointer;array[arraypointer].string_starting_pointer=copy_string_starting_pointer;}//handling a realloc failure
            else{printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");arraypointer--;break;}//string realloc fail handler
        
        }
        copy_string_starting_pointer[wordpointer]=(char)character_being_read;wordpointer++;wordlength++;
    }
    else if((character_being_read==32||character_being_read==10)&&bool_in_word==1){//we are in word and our next read char is blankspace/newline, so we start preparation for the next word by resetting word pointer and size to 0
        if(wordlength==allocated_size){temp_r_pointer=realloc(copy_string_starting_pointer,allocated_size+1);//if our word length reaches max allocated size, we reallocate one more byte to add the null character}
            if(temp_r_pointer!=NULL){copy_string_starting_pointer=temp_r_pointer;array[arraypointer].string_starting_pointer=copy_string_starting_pointer;copy_string_starting_pointer[wordpointer]=(char)0;}
            else{printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");arraypointer--;break;}}//string realloc fail handler
        else{copy_string_starting_pointer[wordpointer]=(char)0;
            temp_r_pointer=realloc(copy_string_starting_pointer,wordlength+1);//if our word hasnt reached the max allocated length, we add the null character and reallocate the memory block to just consume enough space to fit the string and the null character
            if(temp_r_pointer!=NULL){copy_string_starting_pointer=temp_r_pointer;array[arraypointer].string_starting_pointer=copy_string_starting_pointer;}
            else{printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");break;}//string realloc fail handler. no arraypointer-- here because the null character has already been added, so we can print this word
        allocated_size=20;
        copyarray[arraypointer].length=wordlength;
        bool_in_word=0;arraypointer++;wordpointer=0;wordlength=0;arraysize++;}
    }
}
    if((bool_in_word==1)&&(character_being_read==-1)){//handles adding a null character to the last word when eof is reached and loop ends
        if(wordlength==allocated_size){temp_r_pointer=realloc(copy_string_starting_pointer,allocated_size+1);//if our word length reaches max allocated size, we reallocate one more byte to add the null character
            if(temp_r_pointer!=NULL){copy_string_starting_pointer=temp_r_pointer;array[arraypointer].string_starting_pointer=copy_string_starting_pointer;copy_string_starting_pointer[wordpointer]=(char)0;
            array[arraypointer].length=wordlength;arraysize++;}
            else{printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");arraypointer--;}
        }
        else{copy_string_starting_pointer[wordpointer]=(char)0;array[arraypointer].length=wordlength;
            temp_r_pointer=realloc(copy_string_starting_pointer,wordlength+1);//if our word hasnt reached the max allocated length, we add the null character and reallocate the memory block to just consume enough space to fit the string and the null character
            if(temp_r_pointer!=NULL){copy_string_starting_pointer=temp_r_pointer;array[arraypointer].string_starting_pointer=copy_string_starting_pointer;arraysize++;}
            else{printf("There is a memory allocation failure, possibly due to lack of memory. Printing all words stored till now and exiting program\n");arraysize++;}//string realloc fail handler. no arraypointer-- here because the null character has already been added, so we can print this word   
        }}
//-------------------------------------------------------------------------- parsing part of the code is over, now printing and freeing is next
for(int i=0;i<arraysize;i++){
    printf("Word: %s    Length: %d\n",array[i].string_starting_pointer,array[i].length);
}//printing all the words and their lengths
for(int i=0;i<=arraypointer;i++){
    free(array[i].string_starting_pointer);
}//freeing all the strings in the array
free(array);//freeing the main array itself
fclose(fptr);
}
void file_given_checker(){
    if(global_c<2){printf("No File has been given, please give a file");exit(0);}
}