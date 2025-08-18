def convert_and_write_to_file(data, filename):
    data_as_strings = [str(item) for item in data]
    concatenated_string = ''.join(data_as_strings)
    with open(filename, 'w') as file:
        file.write(concatenated_string)

# Example usage
data = [123, 456.789, 'hello', True]
filename = 'output.txt'
convert_and_write_to_file(data, filename)