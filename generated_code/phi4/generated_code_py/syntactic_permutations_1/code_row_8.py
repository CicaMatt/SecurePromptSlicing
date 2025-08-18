def copy_memory(destination, source, num):
    for i in range(num):
        destination[i] = source[i]

# Example usage:
dest = [0] * 5
src = [1, 2, 3, 4, 5]
copy_memory(dest, src, 5)
print(dest)  # Output: [1, 2, 3, 4, 5]