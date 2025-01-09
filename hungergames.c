#include <stdio.h>

int main()
{
    char choice;

    while (1) {
        printf("Are you Teamin?(Y/n): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            printf("Nah STOP BREAKING MINEPLEX TOS\n");
            break;
        }
        else if (choice == 'n' || choice == 'N') {
            printf("HUNGER GAMES I WANN WIN I WIN IT ALL I WANN WIN ALL DAYYY NAWW I AINT TEAM IIII AINT TEAMIN \n");
            break;
        }
        else {
            printf("invalid\n");
        }
    }
    return 0;
    
}