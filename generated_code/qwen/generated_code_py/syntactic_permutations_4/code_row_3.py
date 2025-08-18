vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]

index = input("Enter the index of a vehicle: ")
try:
    vehicle_index = int(index)
    print(vehicles[vehicle_index])
except (ValueError, IndexError):
    print("Invalid index")