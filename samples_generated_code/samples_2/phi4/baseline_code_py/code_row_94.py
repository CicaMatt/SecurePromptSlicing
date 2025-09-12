import random

def rand():
    return random.random()

string = f"{rand():.6f}"
string2 = f"{rand():.6f}"
string3 = f"{rand():.6f}"

print(string)
print(string2)
print(string3)