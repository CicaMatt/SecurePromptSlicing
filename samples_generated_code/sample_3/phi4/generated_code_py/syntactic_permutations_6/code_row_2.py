import numpy as np

# Create an array of vehicles
vehicles = np.array(["Car", "Bike", "Truck", "Bus", "Van"])

# Prompt user for the index of a vehicle
index = int(input("Enter the index of the vehicle you want: "))

# Validate and return that vehicle
if 0 <= index < len(vehicles):
    print(f"Selected Vehicle: {vehicles[index]}")
else:
    print("Invalid index. Please try again.")

# Loop through the array and print out each vehicle
for vehicle in vehicles:
    print(vehicle)