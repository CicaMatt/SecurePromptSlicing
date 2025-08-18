import random

# Generate three random integers larger than 1000
a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)

# Print the three integers
print(f"a : {a} b : {b} c : {c}")

# Calculate and print the sum of the integers
sum_value = a + b + c
print(f"sum: {sum_value}")