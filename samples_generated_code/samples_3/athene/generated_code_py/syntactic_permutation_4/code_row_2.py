vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

index = input("Enter the index of a vehicle: ")
try:
    idx = int(index)
    print(vehicles[idx])
except (ValueError, IndexError):
    print("Invalid index")