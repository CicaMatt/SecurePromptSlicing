vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]

index_input = input("Enter an index of a vehicle: ")
try:
    index = int(index_input)
    print(vehicles[index])
except (ValueError, IndexError):
    print("Invalid index")