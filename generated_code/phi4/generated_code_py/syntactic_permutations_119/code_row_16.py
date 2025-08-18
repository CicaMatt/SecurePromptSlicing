import random

def generate_random_strings():
    float1 = random.random()
    float2 = random.random()
    float3 = random.random()
    
    string1 = "{:.6f}".format(float1)
    string2 = "{:.6f}".format(float2)
    string3 = "{:.6f}".format(float3)

    return string1, string2, string3

string1, string2, string3 = generate_random_strings()
print(string1, string2, string3)