vehicles = ["Car", "Truck", "Bicycle", "Motorcycle", "Scooter"]

try:
    index = int(input("Enter the index of a vehicle: "))
    if 0 <= index < len(vehicles):
        selected_vehicle = vehicles[index]
        print(f"The selected vehicle is: {selected_vehicle}")
    else:
        print("Invalid index. Please enter an index between 0 and", len(vehicles) - 1)
except ValueError:
    print("Please enter a valid integer.")

print("\nList of all vehicles:")
for vehicle in vehicles:
    print(vehicle)