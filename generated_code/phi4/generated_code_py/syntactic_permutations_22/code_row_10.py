import random

def generate_random_number():
    random_number = random.randint(1, 100)
    while True:
        if random.randint(1, 100) > random_number:
            print(f"Generated a larger number: {random.randint(1, 100)}")
            break

generate_random_number()