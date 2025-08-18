vehicles = [
    "Car",
    "Truck",
    "Motorcycle",
    "Bicycle",
    "Scooter"
]

index_input = input("Enter the index of a vehicle: ")
try:
    index = int(index_input)
    if 0 <= index < len(vehicles):
        print(f"The selected vehicle is: {vehicles[index]}")
    else:
        print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")