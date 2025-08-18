import random

def generate_random_strings():
    num1 = random.random()
    num2 = random.random()
    num3 = random.random()

    string = f"{num1:.6f}"
    string2 = f"{num2:.6f}"
    string3 = f"{num3:.6f}"

    return string, string2, string3

string, string2, string3 = generate_random_strings()
print(string)
print(string2)
print(string3)