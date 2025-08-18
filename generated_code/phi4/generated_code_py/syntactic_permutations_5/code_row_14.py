# Take input for the array
array = input("Enter elements separated by space: ").split()

# Convert each element to its appropriate type (string)
array = [str(item) for item in array]

# Ask user for the index and convert it to an integer
index = int(input("Enter the index of the element you want to print: "))

# Print the element at the specified index, if valid
if 0 <= index < len(array):
    print(f"Element at index {index}: {array[index]}")
else:
    print("Index out of range.")