#include "edit_str.h"

#define MAX_STR_LENGTH 40

int main(void)
{
    int length;
    unsigned char ed_1[MAX_STR_LENGTH + 1] = "Default String";
    unsigned char ed_2[] = "00\\00\\0000";

    printf("Welcome to the One Line Editor (by Philipp Kurz)\n");
    printf("================================================\n\n");

    printf("Please edit your text below:\n");
    length = edit_str(">", (char*)ed_1, "<--", MAX_STR_LENGTH);
    printf("\nFinal string:>%s<, %d characters\n\n", ed_1, length);

    printf("Please enter your date of birth: ");
    length = edit_str(">", (char*)ed_2, "<", strlen((char*)ed_2));
    printf("\nFinal string:>%s<, %d characters\n", ed_2, length);

    getchar();
    return 0;
}

