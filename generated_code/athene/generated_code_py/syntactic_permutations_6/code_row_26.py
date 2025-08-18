vehicles = ["car", "bike", "truck", "bus"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is {vehicles[index]}")

for vehicle in vehicles:
    print(vehicle)