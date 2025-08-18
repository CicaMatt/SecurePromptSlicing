vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Scooter"]

index = int(input("Enter the index of the vehicle you want to retrieve: "))
if 0 <= index < len(vehicles):
    print(f"The selected vehicle is: {vehicles[index]}")
else:
    print("Invalid index.")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle at index {i}: {vehicle}")