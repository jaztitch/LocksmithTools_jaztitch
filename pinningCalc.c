#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_KEYS 7
#define PIN_COUNT 6
#define MAX_PINS_PER_STACK 5

int keyNum;

int welcome(){
    printf("\rWelcome to the pinning calculator.\n");
    sleep(1.5);
    printf("\rHow many keys do you need to work this lock?\nEnter amount (1-7): ");
    scanf("%d", &keyNum);
}

int main(void) {
    char keys[MAX_KEYS][PIN_COUNT + 1];
    int bottomPins[PIN_COUNT] = {0};
    int masterStacks[PIN_COUNT][MAX_PINS_PER_STACK] = {{0}};
    int stackHeights[PIN_COUNT] = {0};

welcome();

    if (keyNum < 1 || keyNum > MAX_KEYS) {
        printf("Unsupported number of keys.\n");
        welcome();
    }

    for (int k = 0; k < keyNum; k++) {
        printf("Enter 6-digit key #%d: ", k + 1);
        scanf("%6s", keys[k]);
    }

    for (int i = 0; i < PIN_COUNT; i++) {
        int min = keys[0][i] - '0';

        for (int k = 1; k < keyNum; k++) {
            int digit = keys[k][i] - '0';
            if (digit < min) min = digit;
        }

        bottomPins[i] = min;

        for (int k = 0; k < keyNum; k++) {
            int diff = (keys[k][i] - '0') - min;

            if (diff > 0) {
                int exists = 0;
                for (int j = 0; j < stackHeights[i]; j++) {
                    if (masterStacks[i][j] == diff) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists && stackHeights[i] < MAX_PINS_PER_STACK) {
                    masterStacks[i][stackHeights[i]++] = diff;
                }
            }
        }
    }

    int maxHeight = 0;
    for (int i = 0; i < PIN_COUNT; i++) {
        if (stackHeights[i] > maxHeight) {
            maxHeight = stackHeights[i];
        }
    }

    printf("\nChamber:     ");
    for (int i = 0; i < PIN_COUNT; i++) {
        printf("%-3d", i + 1);
    }
    printf("\n");

    for (int level = maxHeight - 1; level >= 0; level--) {
        printf("             ");
        for (int i = 0; i < PIN_COUNT; i++) {
            if (level < stackHeights[i]) {
                printf("%-3d", masterStacks[i][level]);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }

    printf("Bottom Pin:  ");
    for (int i = 0; i < PIN_COUNT; i++) {
        printf("%-3d", bottomPins[i]);
    }
    printf("\n");

    return 0;
}

