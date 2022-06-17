#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


int simulation(int switch_var) { // A single simulation of the game show.
    int doors[3] = {0, 0, 0};
    doors[rand() % 3] = 1; // Make a random door the prize.
    int choice = rand() % 3; // The player chooses a door to stand next to.

    if (switch_var == 1) {
        for (int door_index = 0;door_index < 3; door_index++) {
            if (door_index != choice && doors[door_index] == 0) { // Simulate the host picking a door to reveal.
                return doors[3 - choice - door_index]; // Use the revealed door and the player's door to find the remaining door to switch to.
            }
        }
    } else {
        // If the player doesn't switch, it doesn't matter what the host picks.
        return doors[choice];
    }
}


int main() {
    srand(time(0)); // Randomizer seed.
    int win_losses[4] = {
        0, 0, // Wins and losses for not switching.
        0, 0, // Wins and losses for switching.
    };
    int time_limit = 60;
    int switch_ = 1; // 1 = True, 0 = False
    int result;
    printf("Running simulation for %d seconds...", time_limit);
    int current_time = time(0);
    while (time(0) - current_time <= time_limit) {
        switch_ = 1 - switch_;
        result = simulation(switch_);
        win_losses[switch_ * 2 + (1 - result)]++; // Weird equation for 2D arrays. Records result of simulation.

    }
    int total_sims = win_losses[0] + win_losses[1] + win_losses[2] + win_losses[3];
    
    printf("After %d seconds, the program ran %d simulations.\n", time_limit, total_sims);
    printf("The player won %d times when they switched doors.\n", win_losses[2]);
    printf("The player won %d times when they didn't switch doors.\n", win_losses[0]);
    double switch_prob = (double)win_losses[2] / ((double)win_losses[2] + (double)win_losses[3]) * (double)100;
    double stay_prob   = (double)win_losses[0] / ((double)win_losses[0] + (double)win_losses[1]) * (double)100;
    printf("The player wins %lf%% of the time when they switch.\n", switch_prob);
    printf("The player wins %lf%% of the time when they don't switch.\n", stay_prob);
    
    return 0;
}