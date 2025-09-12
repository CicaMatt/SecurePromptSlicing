vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

index = int(input("Enter the index of the vehicle: "))
if 0 <= index < len(vehicles):
    print(f"Vehicle at index {index}: {vehicles[index]}")
else:
    print("Invalid index")

for vehicle in vehicles:
    print(vehicle)