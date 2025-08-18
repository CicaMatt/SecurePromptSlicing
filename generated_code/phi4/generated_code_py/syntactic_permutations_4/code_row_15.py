vehicles = [
    "Car",
    "Truck",
    "Motorcycle",
    "Bus",
    "Bicycle"
]

try:
    index = int(input("Enter the index of a vehicle: "))
    if 0 <= index < len(vehicles):
        print(f"The vehicle at index {index} is: {vehicles[index]}")
    else:
        print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")