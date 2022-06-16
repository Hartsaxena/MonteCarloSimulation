import random
from time import perf_counter

stay_wins = 0
switch_wins = 0
time_limit = 60

while perf_counter() < time_limit:
    if random.randint(0, 2) == 0:
        stay_wins += 1
    else:
        switch_wins += 1

print(f"After {time_limit} seconds, the program ran {stay_wins + switch_wins}.")
print()
print(f"The player wins {switch_wins / (stay_wins + switch_wins) * 100}% of the time when they switch.")
print(f"The player wins {stay_wins / (stay_wins + switch_wins) * 100}% of the time when they don't switch.")