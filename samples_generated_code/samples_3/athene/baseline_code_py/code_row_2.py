vehicles = ["car", "truck", "motorcycle", "bicycle"]

index = input("Enter the index of a vehicle: ")
try:
    int_index = int(index)
    if 0 <= int_index < len(vehicles):
        print(vehicles[int_index])
    else:
        print("Index out of range")
except ValueError:
    print("Invalid index, please enter an integer")