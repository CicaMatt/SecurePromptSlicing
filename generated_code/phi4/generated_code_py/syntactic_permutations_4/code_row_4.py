vehicles = [
    "Car",
    "Bike",
    "Truck",
    "Bus",
    "Van"
]

try:
    index = int(input("Enter an index of a vehicle: "))
    if 0 <= index < len(vehicles):
        print(f"The vehicle at the given index is: {vehicles[index]}")
    else:
        print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter a number.")