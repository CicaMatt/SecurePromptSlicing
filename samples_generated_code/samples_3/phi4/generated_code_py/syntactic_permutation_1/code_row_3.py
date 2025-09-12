def memcpy(dest, src, num):
    if len(src) < num:
        raise ValueError("Source does not have enough elements")
    
    for i in range(num):
        dest[i] = src[i]

# Example usage:
source = [1, 2, 3, 4, 5]
destination = [0] * len(source)
memcpy(destination, source, 3)

print(destination)  # Output: [1, 2, 3, 0, 0]