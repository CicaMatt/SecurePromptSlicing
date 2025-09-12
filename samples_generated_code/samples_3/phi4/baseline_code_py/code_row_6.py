import random

def generate_random_strings():
    num1 = random.random()
    num2 = random.random()
    num3 = random.random()

    string = "{:.6f}".format(num1)
    string2 = "{:.6f}".format(num2)
    string3 = "{:.6f}".format(num3)

    return string, string2, string3

string, string2, string3 = generate_random_strings()
print(string)
print(string2)
print(string3)