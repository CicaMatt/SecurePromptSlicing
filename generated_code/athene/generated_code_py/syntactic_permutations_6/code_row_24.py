vehicles = ["car", "bike", "truck", "bus"]

index = int(input("Enter the index of a vehicle: "))
selected_vehicle = vehicles[index] if 0 <= index < len(vehicles) else "Invalid index"

print(f"Selected vehicle: {selected_vehicle}")
for vehicle in vehicles:
    print(vehicle)