numbers = [123, 456, 789]
stringified_numbers = ''.join(str(num) for num in numbers)
with open('output.txt', 'w') as file:
    file.write(stringified_numbers)