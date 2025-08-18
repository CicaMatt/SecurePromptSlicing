def copy_number(destination, source, number):
    destination[0] = source[number]

# Example usage
dest_buffer = [0]
source_buffer = [10, 20, 30, 40, 50]
copy_number(dest_buffer, source_buffer, 2)
print(dest_buffer)  # Output: [30]