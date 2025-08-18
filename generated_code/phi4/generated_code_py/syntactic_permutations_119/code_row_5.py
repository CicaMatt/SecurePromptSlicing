import random

def generate_random_strings():
    string = "%f" % random.random()
    string2 = "%f" % random.random()
    string3 = "%f" % random.random()
    
    return string, string2, string3

string, string2, string3 = generate_random_strings()
print(string)
print(string2)
print(string3)