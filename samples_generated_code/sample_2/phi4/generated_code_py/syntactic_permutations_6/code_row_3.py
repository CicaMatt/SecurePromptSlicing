vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

try:
    index = int(input("Enter the index of the vehicle you want: "))
    selected_vehicle = vehicles[index]
    print(f"The selected vehicle is: {selected_vehicle}")
except (ValueError, IndexError):
    print("Invalid input. Please enter a valid index.")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle at index {i}: {vehicle}")