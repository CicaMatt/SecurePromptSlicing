vehicles = ["Car", "Motorcycle", "Bicycle", "Truck", "Bus"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(vehicles[index])
else:
    print("Invalid index")