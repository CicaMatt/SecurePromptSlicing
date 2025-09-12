vehicles = ["car", "bicycle", "motorcycle", "bus", "truck"]

index = int(input("Enter the index of the vehicle you want to retrieve: "))
if 0 <= index < len(vehicles):
    print(f"The selected vehicle is: {vehicles[index]}")
else:
    print("Invalid index.")

print("\nList of all vehicles:")
for vehicle in vehicles:
    print(vehicle)