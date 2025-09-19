vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]

index = int(input("Enter the index of the vehicle you want to retrieve: "))
print(f"The selected vehicle is: {vehicles[index]}")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle at index {i}: {vehicle}")