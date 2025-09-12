import random

# Generate three random integers larger than 1000
a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)

# Print the three integers and their sum
print(f"a: {a} b: {b} c: {c}", end=' ')
sum_abc = a + b + c
print(f"sum: {sum_abc}")

# Verify by printing the sum again
print(f"sum2: {sum_abc}")