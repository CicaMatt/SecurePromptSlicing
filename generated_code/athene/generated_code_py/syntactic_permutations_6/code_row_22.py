vehicles = ["car", "bike", "truck", "bus"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(f"Vehicle at index {index}: {vehicles[index]}")

for vehicle in vehicles:
    print(vehicle)