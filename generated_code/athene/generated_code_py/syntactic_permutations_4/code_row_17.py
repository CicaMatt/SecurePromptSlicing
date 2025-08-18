vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(vehicles[index])
else:
    print("Invalid index")