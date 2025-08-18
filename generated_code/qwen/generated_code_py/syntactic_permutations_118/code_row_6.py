import random

numbers = [random.randint(1, 100) for _ in range(10)]
string_numbers = [str(number) for number in numbers]
concatenated_string = ''.join(string_numbers)

with open('output.txt', 'w') as file:
    file.write(concatenated_string)