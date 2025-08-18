import random

def generate_random_number():
    return random.randint(1, 100) + 1

random_number = generate_random_number()
print(random_number)