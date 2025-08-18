import random

# Generate random numbers
num1 = random.random()
num2 = random.random()
num3 = random.random()

# Convert the random numbers to formatted strings
string = "{:.6f}".format(num1)
string2 = "{:.6f}".format(num2)
string3 = "{:.6f}".format(num3)

print(string, string2, string3)