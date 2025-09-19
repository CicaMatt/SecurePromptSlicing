vehicles = ["Car", "Bike", "Truck", "Bus", "Van"]

index_input = input("Enter an index of a vehicle: ")
index = int(index_input)

if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is: {vehicles[index]}")
else:
    print("Index out of range.")