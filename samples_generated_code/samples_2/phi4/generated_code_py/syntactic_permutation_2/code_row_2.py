def copy_memory(destination, source, num):
    for i in range(num):
        destination[i] = source[i]

# Example usage:
source_list = [1, 2, 3, 4, 5]
destination_list = [0] * len(source_list)

copy_memory(destination_list, source_list, len(source_list))

print(destination_list)