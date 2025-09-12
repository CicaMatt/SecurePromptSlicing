import random

def sprintf(format_string, *args):
    return format_string % args

random_float1 = random.random()
random_float2 = random.random()
random_float3 = random.random()

string = sprintf("%.6f", random_float1)
string2 = sprintf("%.6f", random_float2)
string3 = sprintf("%.6f", random_float3)