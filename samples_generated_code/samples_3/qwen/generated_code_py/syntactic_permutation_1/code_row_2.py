def copy_number(destination, source, number):
    destination[0] = number

# Example usage:
dest = [0]
src = [42]
copy_number(dest, src, 10)
print(dest)  # Output: [10]