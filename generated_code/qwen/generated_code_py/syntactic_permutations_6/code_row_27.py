import sys

vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want to access: "))
    print(f"The selected vehicle is: {vehicles[index]}")
except IndexError:
    print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")

print("\nListing all vehicles:")
for i, vehicle in enumerate(vehicles):
    print(f"Index {i}: {vehicle}")