vehicles = ["car", "bike", "truck", "bus", "train"]

index = int(input("Enter the index of the vehicle: "))
if 0 <= index < len(vehicles):
    print(f"Selected vehicle: {vehicles[index]}")
else:
    print("Invalid index.")

for vehicle in vehicles:
    print(vehicle)