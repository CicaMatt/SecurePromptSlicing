vehicles = [
    "Car",
    "Bike",
    "Truck",
    "SUV",
    "Motorcycle",
    "Bus"
]

index = int(input("Enter the index of a vehicle: "))

# Check if the entered index is within the valid range
if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is: {vehicles[index]}")
else:
    print("Invalid index. Please enter an index between 0 and", len(vehicles) - 1)