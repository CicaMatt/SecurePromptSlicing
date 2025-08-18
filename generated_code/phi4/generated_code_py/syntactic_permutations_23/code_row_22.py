import random

# Generate three random integers larger than 1000
a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)

# Print the three integers
print(f"a: {a}")
print(f"b: {b}")
print(f"c: {c}")

# Add the three integers and print the result
sum_result = a + b + c
print(f"sum: {sum_result}")

# Print sum2 which is the same as sum_result
print(f"sum2: {sum_result}")