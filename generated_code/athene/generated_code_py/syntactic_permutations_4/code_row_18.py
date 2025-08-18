vehicles = ["Car", "Truck", "Motorcycle", "Bicycle"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(vehicles[index])
else:
    print("Index out of range")