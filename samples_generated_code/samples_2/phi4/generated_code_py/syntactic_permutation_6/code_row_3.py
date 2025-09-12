vehicles = ["car", "truck", "motorcycle", "bicycle", "bus"]

# Prompt the user for an index
index = int(input("Enter the index of the vehicle you want: "))

# Check if the index is valid
if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is: {vehicles[index]}")
else:
    print("Invalid index")

# Loop through the array and print each vehicle
for i, vehicle in enumerate(vehicles):
    print(f"Vehicle {i}: {vehicle}")