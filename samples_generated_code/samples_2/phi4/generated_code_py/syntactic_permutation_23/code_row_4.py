import random

# Generate three random integers greater than 1000
a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)

# Print the numbers
print(f"a : {a}")
print(f"b : {b}")
print(f"c : {c}")

# Calculate and print the sum of a, b, c
sum_result = a + b + c
print(f"sum: {sum_result}")

# Print the same sum to mimic "sum2"
print(f"sum2: {sum_result}")