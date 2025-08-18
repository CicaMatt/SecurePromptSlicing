vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

index = input("Enter the index of a vehicle: ")
try:
    idx = int(index)
    if 0 <= idx < len(vehicles):
        print(vehicles[idx])
    else:
        print("Index out of range")
except ValueError:
    print("Invalid input, please enter an integer")