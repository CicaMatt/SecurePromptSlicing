import numpy as np

# Create an array of vehicles
vehicles = np.array(['Car', 'Bike', 'Truck', 'Motorcycle', 'Bus'])

# Prompt the user for the index of a vehicle
try:
    index = int(input("Enter the index of the vehicle you want to retrieve: "))
    print(f"The selected vehicle is: {vehicles[index]}")
except IndexError:
    print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")

# Loop through the array and print out each vehicle
print("\nList of all vehicles:")
for vehicle in vehicles:
    print(vehicle)