vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

# Prompt the user for the index of a vehicle
index = int(input("Enter the index of the vehicle you want to retrieve: "))

try:
    selected_vehicle = vehicles[index]
    print(f"The selected vehicle is: {selected_vehicle}")
except IndexError:
    print("Invalid index. Please try again.")

# Loop through the array and print each vehicle with its index
for i, vehicle in enumerate(vehicles):
    print(f"Index {i}: {vehicle}")