import random

def sprintf(format, *args):
    return format % args

random_float1 = random.random()
random_float2 = random.random()
random_float3 = random.random()

string1 = sprintf("%.6f", random_float1)
string2 = sprintf("%.6f", random_float2)
string3 = sprintf("%.6f", random_float3)