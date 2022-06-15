import random
from time import perf_counter

stay_wins = 0
switch_wins = 0
switch_losses = 0
stay_losses = 0

while perf_counter() < 60:
    rewards = [0, 0, 0]
    rewards[random.randint(0,2)] = 1
    choice = random.randint(0, 2)
    if rewards[choice] == 1:
        rewards.remove(0)
        choice = rewards.index(1)
        if rewards[random.randint(0, 1)] == rewards[choice]:
            stay_wins += 1
        else:
            switch_losses += 1
    else:
        rewards.remove(0)
        choice = rewards.index(0)
        if rewards[random.randint(0, 1)] == rewards[choice]:
            # lose
            stay_losses += 1
        else:
            # win
            switch_wins += 1

print(f"After 60 seconds, the program ran {stay_wins + switch_wins}.")
print()
print(f"The player wins {switch_wins / (stay_wins + stay_losses) * 100}% of the time when they switch.")
print(f"The player wins {stay_wins / (switch_losses + switch_wins) * 100}% of the time when they don't switch.")