import random

def sprintf(format, *args):
    return format % args

string = sprintf("%.6f", random.random())
string2 = sprintf("%.6f", random.random())
string3 = sprintf("%.6f", random.random())

print(string)
print(string2)
print(string3)