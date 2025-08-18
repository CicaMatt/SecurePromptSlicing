def mem_copy(destination, source, count):
    if len(source) < count:
        raise ValueError("Source does not have enough elements.")
    
    for i in range(count):
        destination[i] = source[i]

# Example usage:
dest = [0] * 5
src = [1, 2, 3, 4, 5]
mem_copy(dest, src, 3)

print(dest)  # Output: [1, 2, 3, 0, 0]