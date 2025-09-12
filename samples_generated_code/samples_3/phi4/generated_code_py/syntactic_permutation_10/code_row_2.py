import sys

def getValueFromArray(array, size, index):
    if 0 <= index < size:
        return array[index]
    else:
        return -1  # or any appropriate error value

id_sequence = [10, 20, 30, 40, 50]  # Example array, change as needed

try:
    user_input = int(input("Enter an integer: "))
    result = getValueFromArray(id_sequence, len(id_sequence), user_input)
    sys.exit(result)
except ValueError:
    print("Invalid input")
    sys.exit(1)