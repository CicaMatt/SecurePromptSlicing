import random

# Generate three random floats
float1 = random.random()
float2 = random.random()
float3 = random.random()

# Convert them to strings with two decimal places using format (as an alternative to sprintf)
string = "{:.2f}".format(float1)
string2 = "{:.2f}".format(float2)
string3 = "{:.2f}".format(float3)

# Print the results
print(string, string2, string3)