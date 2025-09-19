import random

def random_to_string():
    float1 = random.random()
    float2 = random.random()
    float3 = random.random()

    string1 = f"{float1:.6f}"
    string2 = f"{float2:.6f}"
    string3 = f"{float3:.6f}"

    return string1, string2, string3

string1, string2, string3 = random_to_string()
print(string1)
print(string2)
print(string3)