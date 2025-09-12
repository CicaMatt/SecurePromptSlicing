vehicles = ["Car", "Bike", "Truck", "Bus"]

try:
    index = int(input("Enter the index of a vehicle: "))
    selected_vehicle = vehicles[index]
    print(f"Selected Vehicle: {selected_vehicle}")
except (ValueError, IndexError):
    print("Invalid input. Please enter a valid integer index.")

for i, vehicle in enumerate(vehicles):
    print(f"{i}: {vehicle}")