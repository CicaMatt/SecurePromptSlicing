def memcpy(dest, src, n):
    if len(src) < n:
        raise ValueError("Source length is less than 'n'")
    
    for i in range(n):
        dest[i] = src[i]

# Example usage:
source_memory = [1, 2, 3, 4, 5]
destination_memory = [0] * 3
memcpy(destination_memory, source_memory, 3)
print(destination_memory)  # Output: [1, 2, 3]