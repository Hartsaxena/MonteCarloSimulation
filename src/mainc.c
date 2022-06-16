#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int sim() {
    int choice = rand() % 3;
    if (choice == 0) {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    srand(time(0));
    int stay_wins = 0;
    int switch_wins = 0;
    int time_limit = 60;

    int current_time = time(0);
    while (time(0) - current_time <= time_limit) {
        if (sim() == 1) {
            stay_wins++;
        } else {
            switch_wins++;
        }
    }
    printf("After %d seconds, the program ran %d simulations.", time_limit, stay_wins + switch_wins);
}