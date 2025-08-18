vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index = int(input("Enter an index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(vehicles[index])
else:
    print("Index out of range.")