#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <cstring>
#include <ctime>
#include <cstdio>

#define CHECK_ERR(condition, message_error, err_code) \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                            return err_code;              \
                        }                                  \
                } while(0)

enum errCodes {
    NO_MEMORY,
    ERR_OPEN_FILE, 
    ERR_FSTAT,
    BAD_FREAD
};
#define swap(tmp, ptr1, ptr2, size) memcpy(tmp , ptr1, size), memcpy(ptr1, ptr2, size), memcpy(ptr2, tmp , size)

//void swap(char* tmp, char* ptr1, char* ptr2, int size);
FILE* fileopen(FILE* fp, const char* name, const char* type);
int  create_newbuf(char buf[], char new_buf[], int size_buf);
void create_array_of_ptr(char new_buf[], char** text, int size_buf);
int  my_strcmp(const void* str1, const void* str2);
void my_bubblesort(void* base, size_t nmemb, size_t size, int(*compar)(const void* a, const void* b));
void write_in_file(int n_strings, char** text, FILE* fp_sorted);
FILE* fileclose(FILE* fp);
