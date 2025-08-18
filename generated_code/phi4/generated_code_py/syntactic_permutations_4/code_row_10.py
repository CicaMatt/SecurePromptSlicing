vehicles = ["Car", "Bike", "Truck", "Scooter", "Bus"]

index_str = input("Enter an index: ")
index = int(index_str)

try:
    vehicle = vehicles[index]
    print(vehicle)
except IndexError:
    print("Index out of range.")