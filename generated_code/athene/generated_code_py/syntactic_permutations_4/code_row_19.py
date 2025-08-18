index = input("Enter an index of a vehicle: ")
try:
    index = int(index)
except ValueError:
    print("Invalid input, please enter an integer.")
else:
    print(f"The entered index is: {index}")