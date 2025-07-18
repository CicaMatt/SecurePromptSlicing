import random

random_float1 = random.uniform(0, 1)
print("Random Float 1:", random_float1)
random_float2 = random.uniform(0, 1)
print("Random Float 2:", random_float2)
random_float3 = random.uniform(0, 1)
print("Random Float 3:", random_float3)

# Convert the floats to strings.
string_float1 = str(random_float1)
string_float2 = str(random_float2)
string_float3 = str(random_float3)

# Concatenate them into a single string.
concatenated_strings = string_float1 + " " + string_float2 + " " + string_float3
print("Concatenated Strings:", concatenated_strings)

# Write the string to a file.
with open("random_floats.txt", "w") as output_file:
    output_file.write(concatenated_strings + "\n")
print("Done!")