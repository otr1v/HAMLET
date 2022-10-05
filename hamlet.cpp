#include "func.h"

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

// 12. remove fopen, fread, fclose from main()
// 13. check fread return value
// 14. remove double fstat
// 15. add struct line

int main()
{
    FILE* fp, *fp_original, *fp_sorted;
    fp = fileopen(fp, "source.txt", "r");
    CHECK_ERR(fp == NULL, "can't open the file", ERR_OPEN_FILE);
    fp_original = fileopen(fp_original, "output.txt", "w");
    CHECK_ERR(fp_original == NULL, "can't open the file", ERR_OPEN_FILE);
    fp_sorted = fileopen(fp_sorted, "sorted.txt", "w");
    CHECK_ERR(fp_sorted == NULL, "can't open the file", ERR_OPEN_FILE);

    struct stat buffer = {};
    
    int res_fstat = fstat(fileno(fp), &buffer);
    CHECK_ERR(res_fstat == -1, "can't fill the structure stat", ERR_FSTAT);

    int size_buf  = buffer.st_size;
    char* buf     = (char*)calloc(size_buf + 1, sizeof(char));
    char* new_buf = (char*)calloc(size_buf + 1, sizeof(char));
    CHECK_ERR(buf     == NULL, "can't give memory", NO_MEMORY);
    CHECK_ERR(new_buf == NULL, "can't give memory", NO_MEMORY);

    int res_fread = fread(buf, sizeof(char), size_buf, fp);
    CHECK_ERR(res_fread != size_buf, "wrong fread ret value", BAD_FREAD);
// gcc hamlet.cpp -o ham -Wall -Wextra -fsanitize=address
// Makefile
    double start = clock();

    int n_strings = create_newbuf(buf, new_buf, size_buf);

    char* *text = (char**)calloc(n_strings + 1, sizeof(char*));
    CHECK_ERR(text == NULL, "can't give memory", NO_MEMORY);

    create_array_of_ptr(new_buf, text, size_buf);

    my_bubblesort(text, n_strings, sizeof(text[0]), &my_strcmp);
    printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);

    write_in_file(n_strings, text, fp_sorted);
    fwrite(buf, sizeof(char), size_buf, fp_original);

    free(text);
    free(buf);
    free(new_buf);
    fileclose(fp);
    fileclose(fp_sorted);
    fileclose(fp_original);
    return 0;
}


//===================================================================

