import sys # Import the sys module to read command line arguments

# Create an array of elements
elements = ['Hydrogen', 'Helium', 'Lithium']

# Take in a command line argument and convert it to an integer
index = int(sys.argv[1])

# Print the element at that index
print("Element at index", index, "is", elements[index])