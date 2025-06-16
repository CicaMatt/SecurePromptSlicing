num = int(input("Enter an integer: "))
if num < 1 or num > len(myList):
    print("Index out of range")
else:
    print(f"The {num}th element is {myList[num-1]}")