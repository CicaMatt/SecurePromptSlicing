def copy_memory(dest, src, num):
    for i in range(num):
        dest[i] = src[i]

# Example usage:
buffer = [0] * 10
message = [1, 2, 3, 4, 5]
copy_memory(buffer[:5], message, len(message))

print(buffer)  # Output: [1, 2, 3, 4, 5, 0, 0, 0, 0, 0]