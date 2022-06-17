#include <stdio.h> //To use type gcc mainppc.c -fopenmp then a.exe
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void Runner(int time_limit, int* g_win_stay, int* g_lose_stay, int* g_win_switch, int* g_lose_switch);

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

void Runner(int time_limit, int* g_win_stay, int* g_lose_stay, int* g_win_switch, int* g_lose_switch) {
    srand(time(0)); // Randomizer seed.
    int win_losses[4] = {
        0, 0, // Wins and losses for not switching.
        0, 0, // Wins and losses for switching.
    };
    int switch_ = 1; // 1 = True, 0 = False
    int result;
    int current_time = time(0);
    while (time(0) - current_time <= time_limit) {
        switch_ = 1 - switch_;
        result = simulation(switch_);
        win_losses[switch_ * 2 + (1 - result)]++; // Weird equation for 2D arrays. Records result of simulation.
    }
    #pragma omp critical
    *g_win_stay += win_losses[0];
    #pragma omp critical
    *g_lose_stay += win_losses[1];
    #pragma omp critical
    *g_win_switch += win_losses[2];
    #pragma omp critical
    *g_lose_switch += win_losses[3];
}

int main(int argc, char* argv) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    int time_limit = 60;
    int g_win_stay = 0;
    int g_lose_stay = 0;
    int g_win_switch = 0;
    int g_lose_switch = 0;
    printf("Running simulation for %d seconds... \n", time_limit);
    // Start Threading
    #pragma omp parallel num_threads(thread_count)
    Runner(time_limit, &g_win_stay, &g_lose_stay, &g_win_switch, &g_lose_switch);
    // End Threading

    int total_sims = g_win_stay + g_lose_stay + g_win_switch + g_lose_switch;

    printf("After %d seconds, the program ran %d simulations.\n", time_limit, total_sims);
    printf("The player won %d times when they switched doors.\n", &g_win_switch);
    printf("The player won %d times when they didn't switch doors.\n", &g_win_stay);
    double switch_prob = (double)g_win_switch / ((double)g_win_switch + (double)g_lose_switch) * (double)100;
    double stay_prob   = (double)g_win_stay / ((double)g_win_stay + (double)g_lose_stay) * (double)100;
    printf("The player wins %lf%% of the time when they switch.\n", switch_prob);
    printf("The player wins %lf%% of the time when they don't switch.\n", stay_prob);
    
    return 0;
}

