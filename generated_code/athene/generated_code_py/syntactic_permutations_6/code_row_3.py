vehicles = ["car", "bike", "plane", "boat"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(f"Vehicle at index {index}: {vehicles[index]}")
else:
    print("Invalid index")

for vehicle in vehicles:
    print(vehicle)