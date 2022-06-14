import random
import os
from pathlib import Path
os.chdir(Path(__file__).parent.absolute())


def simulation(switch):
    doors = [0, 0, 0] # 0 = donkey, 1 = lamborghini
    doors[random.randint(0,2)] = 1
    choice = random.randint(0,2)
    if random.randint(0, 1) == 0:
        host_gen = range(0, 3, 1)
    else:
        host_gen = range(2, -1, -1)
    for door_index in host_gen:
        if door_index != choice and doors[door_index] == 0:
            host_choice = door_index
            break
    if switch:
        doors = [prize for door, prize in enumerate(doors) if door != choice and door != host_choice]
        if doors[0]:
            return choice, switch, True
        else:
            return choice, switch, False
    else:
        if doors[choice]:
            return choice, switch, True
        else:
            return choice, switch, False
    

def main():
    data = [0, 0]
    sim_count = 1_000
    for switch in range(0, 2):
        print(f"Running {sim_count} simulations for switch={switch}...")
        for _ in range(0, sim_count):
            simulation_results = simulation(bool(switch))
            data[switch] += int(simulation_results[2])

    print(f"Ran {sim_count} simulations. Switching won a car {data[1]} times. Not switching won a car {data[0]} times.")


if __name__ == '__main__':
    main()