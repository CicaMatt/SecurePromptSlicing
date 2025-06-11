import sys

# Read in the first argument, which is the value to be adjusted
value = int(sys.argv[1])

# Set the offset value
offset = 1000

# Add the offset to the read in value
result = offset + value

print("Result after offset:", result)