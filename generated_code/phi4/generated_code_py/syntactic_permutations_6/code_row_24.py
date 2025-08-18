vehicles = ["Car", "Bike", "Truck", "Boat", "Plane"]

try:
    index = int(input("Enter the index of a vehicle: "))
    if 0 <= index < len(vehicles):
        print(f"Selected vehicle: {vehicles[index]}")
    else:
        print("Index out of range.")
except ValueError:
    print("Invalid input. Please enter an integer.")

print("\nList of vehicles:")
for vehicle in vehicles:
    print(vehicle)