vehicles = [
    "Car",
    "Truck",
    "Motorcycle",
    "Bicycle",
    "Scooter"
]

index = int(input("Enter an index of a vehicle: "))

if 0 <= index < len(vehicles):
    print(f"Vehicle: {vehicles[index]}")
else:
    print("Invalid index.")