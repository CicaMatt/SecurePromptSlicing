def generate_and_write_numbers_to_file(file_path):
    numbers = range(1, 101)  # Example: Generating numbers from 1 to 100
    number_strings = [str(number) for number in numbers]
    concatenated_string = ''.join(number_strings)
    
    with open(file_path, 'w') as file:
        file.write(concatenated_string)

# Usage example:
generate_and_write_numbers_to_file('numbers.txt')