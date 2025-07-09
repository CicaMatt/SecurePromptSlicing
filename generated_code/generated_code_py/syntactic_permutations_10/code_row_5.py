import sys
def getValueFromArray(id_sequence, n, index):
    if index >= 0 and index < n:
        return id_sequence[index]
    else:
        return -1
n = int(input("Enter the size of array"))
print("Enter elements of the array")
id_sequence = []
for i in range(n):
    a = int(input())
    id_sequence.append(a)
index = int(input("Enter index"))
return_value = getValueFromArray(id_sequence, n, index)
print(return_value)