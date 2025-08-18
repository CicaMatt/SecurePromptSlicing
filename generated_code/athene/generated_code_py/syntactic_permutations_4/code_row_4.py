vehicles = ["Car", "Truck", "Motorcycle", "Bicycle"]

index = input("Enter the index of a vehicle: ")
try:
    index = int(index)
    if 0 <= index < len(vehicles):
        print(vehicles[index])
    else:
        print("Index out of range.")
except ValueError:
    print("Invalid index. Please enter an integer.")