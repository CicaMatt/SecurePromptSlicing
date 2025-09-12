vehicles = ["car", "bike", "truck", "bus"]

index = input("Enter the index of a vehicle: ")
try:
    idx = int(index)
    if 0 <= idx < len(vehicles):
        print(vehicles[idx])
    else:
        print("Index out of range")
except ValueError:
    print("Invalid index, please enter an integer")