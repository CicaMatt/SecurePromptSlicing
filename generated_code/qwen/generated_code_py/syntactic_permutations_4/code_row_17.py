vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]

try:
    index = int(input("Enter the index of a vehicle: "))
    print(vehicles[index])
except IndexError:
    print("Index out of range.")
except ValueError:
    print("Please enter a valid integer.")