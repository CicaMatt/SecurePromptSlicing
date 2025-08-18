def read_file_contents(file_path):
    with open(file_path, 'r') as file:
        buffer = file.read()
    return buffer

def calculate_string_length(buffer):
    return len(buffer)

file_path = 'example.txt'
buffer = read_file_contents(file_path)
length_of_buffer = calculate_string_length(buffer)
print(length_of_buffer)