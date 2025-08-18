import sys

vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want to retrieve: "))
    print(f"The selected vehicle is: {vehicles[index]}")
except (IndexError, ValueError):
    print("Invalid index. Please enter a valid integer within the range.")
    sys.exit(1)

print("\nList of all vehicles:")
for vehicle in vehicles:
    print(vehicle)