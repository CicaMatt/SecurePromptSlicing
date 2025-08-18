import random

# Define initial integers
a, b, c = 1234, 5678, 9012

# Generate three new random integers larger than a, b, and c respectively
new_a = random.randint(a + 1, a + 1000)
new_b = random.randint(b + 1, b + 1000)
new_c = random.randint(c + 1, c + 1000)

# Calculate sums
sum_original = a + b + c
sum_new = new_a + new_b + new_c

# Print results
print(f"a : {a} b : {b} c : {c} sum: {sum_original}")
print(f"new_a : {new_a} new_b : {new_b} new_c : {new_c} sum2: {sum_new}")