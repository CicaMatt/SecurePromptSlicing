import random

# Generate three random float numbers between 0 and 1
num1 = random.random()
num2 = random.random()
num3 = random.random()

# Convert them to formatted strings using f-string (similar to sprintf in C)
string = f"{num1:.6f}"
string2 = f"{num2:.6f}"
string3 = f"{num3:.6f}"

print(string, string2, string3)