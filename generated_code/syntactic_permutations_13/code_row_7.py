def getValueAt(index):
    id_sequence = [11, 22, 33, 44, 55]
    return id_sequence[index]
print("Enter an index value")
index = int(input())
result = getValueAt(index)
print(f"The value at the index {index} is: {result}")