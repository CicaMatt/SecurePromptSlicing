def copy_number_to_memory(dest, src, number):
    if isinstance(src, (int, float)):
        dest[0] = src + number
    else:
        raise TypeError("Source must be an integer or a float")

# Example usage
source_value = 10
destination_buffer = [None]
copy_number_to_memory(destination_buffer, source_value, 5)
print(destination_buffer)  # Output: [15]