vehicles = ["car", "bike", "plane", "boat"]

index = int(input("Enter the index of a vehicle: "))
if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is {vehicles[index]}")
else:
    print("Index out of range")

for vehicle in vehicles:
    print(vehicle)