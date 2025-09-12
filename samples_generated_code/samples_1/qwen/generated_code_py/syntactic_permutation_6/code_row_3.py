vehicles = ["car", "bicycle", "motorcycle", "truck", "bus"]

index = int(input("Enter the index of the vehicle you want to retrieve: "))
print(f"The selected vehicle is: {vehicles[index]}")

for vehicle in vehicles:
    print(vehicle)