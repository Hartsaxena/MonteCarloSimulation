import random
import time


def simulation(switch):
    '''
    Runs a single iteration of the Monty Hall simulation.
    the argument 'switch' is a boolean value that represents whether to switch doors after the host reveals a goat.
    '''
    doors = [0, 0, 0] # 0 = donkey, 1 = lamborghini
    doors[random.randint(0,2)] = 1 # Make one of the doors the lamborghini
    choice = random.randint(0,2) # The player walks next to a random door.

    if switch: # Simulate the player either switching or not switching doors
        # Find which door the host will reveal, and use it to find the switching position
        for door_index in range(len(doors)):
            if door_index != choice and doors[door_index] == 0: # Rules for which door the host reveals: not the player's choice and not the prize.
                return doors[3 - choice - door_index] # Find which door the player would switch to if they switch
    else:
        return doors[choice]
    

def main():
    win_losses = [[0, 0], [0, 0]] # Amount of wins and losses for not switching doors or switching doors, respectively.
    current_time = time.perf_counter()
    time_limit = 1 # Amount of time the simulation runs
    switch = True
    while time.perf_counter() - current_time < time_limit:
        switch = not switch # Alternate between switching and not switching doors to make simulation more accurate.
        simulation_result = simulation(switch)
        win_losses[int(switch)][1 - simulation_result] += 1 # Record simulation result
    
    total_sims = sum(map(sum, win_losses))
    print(f"After {time_limit} seconds, the program ran {total_sims} simulations.\nThe player won {win_losses[1][0]} times when they switched doors.\nThe player won {win_losses[0][0]} times when they didn't switch doors.")
    print("\nAccording to this iteration of simulations:")
    print(f"The player wins {win_losses[1][0] / sum(win_losses[1]) * 100}% of the time when they switch.")
    print(f"The player wins {win_losses[0][0] / sum(win_losses[0]) * 100}% of the time when they don't switch.")

    


if __name__ == '__main__':
    main()