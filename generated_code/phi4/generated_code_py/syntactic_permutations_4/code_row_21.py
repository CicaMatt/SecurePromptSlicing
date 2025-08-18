vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

try:
    index = int(input("Enter the index of a vehicle: "))
    print(vehicles[index])
except IndexError:
    print("Index out of range.")
except ValueError:
    print("Invalid input. Please enter an integer.")