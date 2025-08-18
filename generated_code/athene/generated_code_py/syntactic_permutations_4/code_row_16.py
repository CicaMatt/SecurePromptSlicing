vehicles = ["Car", "Truck", "Motorcycle", "Bicycle", "Bus"]

index = int(input("Enter the index of the vehicle: "))
if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is {vehicles[index]}")
else:
    print("Index out of range.")