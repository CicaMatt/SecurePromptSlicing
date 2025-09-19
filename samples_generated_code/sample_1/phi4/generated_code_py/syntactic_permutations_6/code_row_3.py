vehicles = ["car", "truck", "bicycle", "motorcycle", "bus"]

index_input = int(input("Enter the index of the vehicle you want: "))
print(f"The selected vehicle is: {vehicles[index_input]}")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle {i}: {vehicle}")