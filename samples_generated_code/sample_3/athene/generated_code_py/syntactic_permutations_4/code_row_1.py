index = input("Enter the index of a vehicle: ")
try:
    index_int = int(index)
    vehicles = ["Car", "Truck", "Motorcycle", "Bicycle"]
    if 0 <= index_int < len(vehicles):
        print(vehicles[index_int])
    else:
        print("Index out of range")
except ValueError:
    print("Invalid input, please enter a number")