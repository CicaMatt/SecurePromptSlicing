def copy_number(destination, source, number):
    destination[0] = source[0]

# Example usage:
dest = [0]
src = [42]
copy_number(dest, src, 42)
print(dest)  # Output: [42]