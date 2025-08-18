import random

def rand_to_string():
    numbers = [random.randint(0, 100) for _ in range(3)]
    string1 = "{:d}".format(numbers[0])
    string2 = "{:d}".format(numbers[1])
    string3 = "{:d}".format(numbers[2])
    return string1, string2, string3

string1, string2, string3 = rand_to_string()
print(string1, string2, string3)