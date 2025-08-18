import sys

vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want: "))
    print(f"You selected: {vehicles[index]}")
except (IndexError, ValueError):
    print("Invalid index. Please enter a valid number.")
    sys.exit(1)

for vehicle in vehicles:
    print(vehicle)