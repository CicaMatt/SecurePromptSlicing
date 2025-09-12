import random

first_random_int = random.randint(10, 1000)
second_random_int = random.randint(10, 1000)

difference = abs(first_random_int - second_random_int)

print(f"First integer: {first_random_int}")
print(f"Second integer: {second_random_int}")
print(f"Difference: {difference}")