#include "func.h"

FILE* fileopen(FILE* fp, const char* name, const char* type)
{
    fp = fopen(name, type);
    return fp;
}

//================================================================

FILE* fileclose(FILE* fp)
{
    fclose(fp);
    return fp;
}
//=================================================================

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

// void swap(char* tmp, char* ptr1, char* ptr2, int size)
// {
//     memcpy(tmp , ptr1, size);
//     memcpy(ptr1, ptr2, size);
//     memcpy(ptr2, tmp , size);
// }


//=======================================================================================

void my_bubblesort(void* base, size_t nmemb, size_t size, int(*compar)(const void* a, const void* b))
{
    int j = 0;
    char** ptr1 = NULL, **ptr2 = NULL;
    char* tmp = NULL;
    char* base1 = (char*) base;
    
    //  ===============================================
    //  |   |    |    |      |
    //  ---------------------------------------------
    // ^          ^
    // | base     |


    for (int i = 0; i < nmemb; i++)
    {
        for (j = i; j < nmemb; j++)
        {
            ptr1 = (char **)(base1 + i * size);
            ptr2 = (char **)(base1 + j * size);
            if (compar(ptr1, ptr2) > 0)
            {
                tmp = *ptr1;
                *ptr1 = *ptr2;
                *ptr2 = tmp;
            }
        }
    } 
}

//====================================================

struct line
{
    char *start;
    int len;
};

int my_strcmp(const void* str1ptr, const void* str2ptr)
{
    const char* str1 = *(const char**) str1ptr;
    const char* str2 = *(const char**) str2ptr;
    
    int idx_str1 = 0, idx_str2 = 0;

    while ((str1[idx_str1] != '\0') && (str2[idx_str2] != '\0'))   //idx < line1->len
    {
        while (!isalpha(str1[idx_str1]))
        {
            idx_str1++;
        }
        while (!isalpha(str2[idx_str2]))
        {
            idx_str2++;
        }
        if (str1[idx_str1] == str2[idx_str2])
        {
            idx_str1++;
            idx_str2++;
        }
        else
        {
            return((int) str1[idx_str1] - (int) str2[idx_str2]);
        }
    }

    return((int) str1[idx_str1] - (int) str2[idx_str2]);
}
