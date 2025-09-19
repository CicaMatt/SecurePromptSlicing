array = [10, 20, 30, 40, 50]
index = int(input("Enter an index: "))
if 0 <= index < len(array):
    print(array[index])
else:
    print("Index out of bounds")