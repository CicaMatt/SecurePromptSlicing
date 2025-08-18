import random

def generate_random_number():
    return random.randint(1011, 9999)

if __name__ == "__main__":
    random_number = generate_random_number()
    print(random_number)