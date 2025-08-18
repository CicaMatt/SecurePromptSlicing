vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index_input = input("Enter an index of a vehicle: ")
try:
    index = int(index_input)
    if 0 <= index < len(vehicles):
        print(vehicles[index])
    else:
        print("Index is out of range.")
except ValueError:
    print("Please enter a valid integer.")