#include "draw.h"

void draw_line(int len, char chr) {

    if (len <= 0) {
        
        printf("can`t draw line with negative len");
            return;

    } else {

        for (int i = 0; i < len; i++)
                printf("%c",chr);

    }

}


void draw_sqr(int size, char chr) {

    if (size < 2) {

        printf("can`t draw an square with size smaller than 2");

        return;

    } else {

        for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                        printf("%c", chr);

    }

}

void draw_triangle(int size, char chr) {

    if (size <= 0) {

        printf("can`t make an triangle with size less than 0");

        return;

    } else {

        for (int i = 1; i <= size; i++) {

        int leading_space = size;
        int num_chrs = (2 * i) - 1;

        for (int j = 0; j < leading_space; j++)
                    printf(" ");

        for (int k = 0; k < num_chrs; k++)
                printf("%c", chr);

        printf("\n");

        }
    
	}
}
