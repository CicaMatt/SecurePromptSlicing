def copy_number(destination, source, num):
    if len(source) >= num:
        destination[:num] = source[:num]
    else:
        raise ValueError("Source does not contain enough elements.")

# Example usage:
source_list = [1, 2, 3, 4, 5]
destination_list = [0] * 3
copy_number(destination_list, source_list, 3)
print(destination_list)  # Output: [1, 2, 3]