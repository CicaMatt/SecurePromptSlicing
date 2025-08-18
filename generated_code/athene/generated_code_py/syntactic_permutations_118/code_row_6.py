import random

numbers = [random.randint(1, 100) for _ in range(10)]
strings = [str(num) for num in numbers]
concatenated_string = ''.join(strings)

with open('output.txt', 'w') as file:
    file.write(concatenated_string)