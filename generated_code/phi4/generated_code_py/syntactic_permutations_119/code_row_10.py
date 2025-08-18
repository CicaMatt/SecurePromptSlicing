import random

def generate_random_strings():
    float1 = random.random()
    float2 = random.random()
    float3 = random.random()

    string = f"{float1:.6f}"
    string2 = f"{float2:.6f}"
    string3 = f"{float3:.6f}"

    return string, string2, string3

string, string2, string3 = generate_random_strings()
print(string)
print(string2)
print(string3)