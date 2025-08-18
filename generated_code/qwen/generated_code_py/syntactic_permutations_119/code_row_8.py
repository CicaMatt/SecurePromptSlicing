import random

# Generate random numbers
num1 = random.randint(0, 100)
num2 = random.randint(0, 100)
num3 = random.randint(0, 100)

# Convert to strings using sprintf equivalent in Python (str.format())
string1 = "{}".format(num1)
string2 = "{}".format(num2)
string3 = "{}".format(num3)

# Output the results
print(string1)
print(string2)
print(string3)