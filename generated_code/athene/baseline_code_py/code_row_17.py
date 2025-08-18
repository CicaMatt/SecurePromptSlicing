array = [1, 2, 3, 4, 5]

index = int(input("Enter an index: "))
if 0 <= index < len(array):
    print(array[index])
else:
    print("Index out of range")