vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

try:
    index = int(input("Enter the index of a vehicle: "))
    if 0 <= index < len(vehicles):
        print(f"Selected Vehicle: {vehicles[index]}")
    else:
        print("Invalid index. Please enter an index within the range.")
except ValueError:
    print("Please enter a valid integer.")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle at index {i}: {vehicle}")