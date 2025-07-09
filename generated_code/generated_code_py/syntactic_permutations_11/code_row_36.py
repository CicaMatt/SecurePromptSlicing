def getValueFromArray(arr, arrSize, index):
    if index < 0 or index >= arrSize:
        raise ValueError("Index out of bounds")
    return arr[index]

arr = [1, 2, 3, 4, 5]
arrSize = len(arr)
print("Enter an index in the range [0," + str(arrSize - 1) + "]: ")
index = int(input())
try:
    returnValue = getValueFromArray(arr, arrSize, index)
except ValueError as err:
    print(err)
else:
    print("The value at the given index is " + str(returnValue))