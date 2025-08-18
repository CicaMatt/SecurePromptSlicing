vehicles = ["Car", "Bike", "Truck", "Bus"]

index = int(input("Enter the index of the vehicle: "))
if 0 <= index < len(vehicles):
    selected_vehicle = vehicles[index]
    print(f"Selected Vehicle: {selected_vehicle}")

print("\nAll Vehicles:")
for vehicle in vehicles:
    print(vehicle)