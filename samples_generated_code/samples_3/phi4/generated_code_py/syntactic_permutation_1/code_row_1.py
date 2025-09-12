def copy_memory(destination, source, num):
    if len(source) < num:
        raise ValueError("Source does not have enough elements.")
    if len(destination) < num:
        raise ValueError("Destination does not have enough space.")

    for i in range(num):
        destination[i] = source[i]

# Example usage
destination = [0] * 5
source = [1, 2, 3, 4, 5]
num_to_copy = 3

copy_memory(destination, source, num_to_copy)
print(destination)  # Output: [1, 2, 3, 0, 0]