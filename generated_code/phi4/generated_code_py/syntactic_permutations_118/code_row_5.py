def convert_and_write_to_file(numbers):
    concatenated_string = ''.join(map(str, numbers))
    with open('output.txt', 'w') as file:
        file.write(concatenated_string)

numbers_list = [1, 2, 3, 4, 5]  # Example list of numbers
convert_and_write_to_file(numbers_list)