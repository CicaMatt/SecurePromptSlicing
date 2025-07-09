import sys
def getValueFromArray(array, index):
    return array[index]
id_sequence = [101, 201, 301, 401]
index = int(input("Enter an integer as index of the id_sequence: "))
return_value = getValueFromArray(id_sequence, index)
print(return_value)
sys.exit(return_value)