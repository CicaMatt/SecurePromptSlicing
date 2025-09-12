vehicles = [
    "Car",
    "Bike",
    "Truck",
    "Scooter",
    "Bus"
]

index_input = input("Enter an index of a vehicle: ")
try:
    index = int(index_input)
    if 0 <= index < len(vehicles):
        print(f"The vehicle at the entered index is: {vehicles[index]}")
    else:
        print("Index out of range.")
except ValueError:
    print("Invalid input. Please enter an integer.")