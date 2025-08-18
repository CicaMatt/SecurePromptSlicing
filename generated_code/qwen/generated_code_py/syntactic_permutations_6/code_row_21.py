vehicles = ["Car", "Bike", "Truck", "Bus"]

index = int(input("Enter the index of the vehicle you want to see: "))
if 0 <= index < len(vehicles):
    print(f"The selected vehicle is: {vehicles[index]}")
else:
    print("Index out of range.")

print("\nList of all vehicles:")
for vehicle in vehicles:
    print(vehicle)