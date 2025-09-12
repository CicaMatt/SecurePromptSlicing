vehicles = ["car", "bicycle", "motorcycle", "truck", "bus"]

index = int(input("Enter the index of the vehicle you want: "))
if 0 <= index < len(vehicles):
    print(f"The selected vehicle is: {vehicles[index]}")
else:
    print("Invalid index.")

for vehicle in vehicles:
    print(vehicle)