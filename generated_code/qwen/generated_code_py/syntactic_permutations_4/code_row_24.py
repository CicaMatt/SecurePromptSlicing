vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]

try:
    index = int(input("Enter the index of a vehicle: "))
    print(vehicles[index])
except (ValueError, IndexError):
    print("Invalid index entered.")