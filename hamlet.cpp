#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <cstring>

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
    ERR_FSTAT
};

void swap(char* tmp, char* ptr1, char* ptr2, int size);
int create_newbuf(char buf[], char new_buf[], int size_buf);
void create_array_of_ptr(char new_buf[], char** text, int size_buf);
int my_cmp(const void* str1, const void* str2);
void my_bubblesort(void* base, size_t nmemb, size_t size, int(*compar)(const void* a, const void* b));
void write_in_file(int n_strings, char** text, FILE* fp_sorted);

//1.openstatus(define error)       done
//2. error fstat                    done
//3. calloc buf nebuf              done
//4. check calloc                  done
//5. valgrind check                 done
//6. qsort or danya sort
//7. char* <- void*(swap func - static)   done
//8. undefined behaviour memcpy     done
//9. i1, i2 change                  dpne
//10. two while !isalpha            done
//11. fseek ftell read how to 
int main()
{
   
    FILE* fp = fopen("source.txt", "r");
    CHECK_ERR(fp == NULL, "can't open the file", ERR_OPEN_FILE);
    FILE* fp_original = fopen("output.txt", "r+");
    FILE* fp_sorted   = fopen("sorted.txt", "r+");

    struct stat buffer = {};
    
    fstat(fileno(fp), &buffer);
    CHECK_ERR(fstat(fileno(fp), &buffer) == -1, "can't fill the structure stat", ERR_FSTAT);

    int size_buf = buffer.st_size;
    char* buf     = (char*)calloc(size_buf + 1, sizeof(char));
    char* new_buf = (char*)calloc(size_buf + 1, sizeof(char));
    CHECK_ERR(buf == NULL,     "can't give memory", NO_MEMORY);
    CHECK_ERR(new_buf == NULL, "can't give memory", NO_MEMORY);

    fread(buf, sizeof(char), size_buf, fp);

    int n_strings = create_newbuf(buf, new_buf, size_buf);

    char* *text = (char**)calloc(n_strings + 1, sizeof(char*));
    CHECK_ERR(text == NULL, "can't give memory", NO_MEMORY);


    create_array_of_ptr(new_buf, text, size_buf);
    my_bubblesort(text, n_strings, sizeof(text[0]), &my_cmp);
   
    write_in_file(n_strings, text, fp_sorted);
    fwrite(buf, sizeof(char), size_buf, fp_original);

    free(text);
    free(buf);
    free(new_buf);
    fclose(fp_original);
    fclose(fp_sorted);
    fclose(fp);
    return 0;
}


//===================================================================



int create_newbuf(char buf[], char new_buf[], int size_buf)
{
    int counter = 0;
    for (int i = 0; i < size_buf; i++)
    {
        if (buf[i] == '\n')
        {
            new_buf[i] = '\0';
            counter += 1;
        }
        else
        {
            new_buf[i] = buf[i];
        }
    }
    return counter + 1;
}

//======================================================================

void create_array_of_ptr(char new_buf[], char** text, int size_buf)
{
    int counter_text = 0;

    for (int i = 0; i < size_buf; i++)
    {
        if (i == 0)
        {
            text[0] = &new_buf[0];
            counter_text++;
        }
        if (new_buf[i] == '\0')
        {
            text[counter_text] = &new_buf[i + 1];
            counter_text++;
        }
    }
}

//====================================================================================

void write_in_file(int n_strings, char** text, FILE* fp_sorted)
{
    for (int i = 0; i < n_strings; i++)
    {
        if (*text[i] != '\0')
        {
            fprintf(fp_sorted, "%s\n", text[i]);
        }
    }
}

//=================================================================================

void swap(char* tmp, char* ptr1, char* ptr2, int size)
{
    memcpy(tmp , ptr1, size);
    memcpy(ptr1, ptr2, size);
    memcpy(ptr2, tmp , size);
}


//=======================================================================================

void my_bubblesort(void* base, size_t nmemb, size_t size, int(*compar)(const void* a, const void* b))
{
    int j = 0;
    char* ptr1 = NULL, *ptr2 = NULL;
    char* tmp = (char*)calloc(1, size);
    char* base1 = (char*) base;
    for (int i = 0; i < nmemb; i++)
    {
        for (j = i; j < nmemb; j++)
        {
            ptr1 = (char *)(base1 + i * size);
            ptr2 = (char *)(base1 + j * size);
            if ((*my_cmp)(ptr1, ptr2) > 0)
            {
                swap(tmp, ptr1, ptr2, size);
            }
        }
    } 
    free(tmp);
}

//====================================================



int my_cmp(const void* str1ptr, const void* str2ptr)
{
    const char* str1 = *(const char**) str1ptr;
    const char* str2 = *(const char**) str2ptr;
    
    int int_str1 = 0, int_str2 = 0;

    while ((str1[int_str1] != '\0') || (str2[int_str2] != '\0'))
    {
        while (!isalpha(str1[int_str1]))
        {
            int_str1++;
        }
        while (!isalpha(str2[int_str2]))
        {
            int_str2++;
        }
        if (str1[int_str1] == str2[int_str2])
        {
            int_str1++;
            int_str2++;
        }
        else
        {
            return((int) str1[int_str1] - (int) str2[int_str2]);
        }
        
    }

    if (str1[int_str1] == str2[int_str2])
    {
        return 0;
    } 
    else
    {
        return((int) str1[int_str1] - (int) str2[int_str2]);
    }
}
