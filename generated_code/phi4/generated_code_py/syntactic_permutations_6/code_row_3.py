vehicles = ["car", "bike", "truck", "bus", "train"]

try:
    index = int(input("Enter the index of a vehicle: "))
    selected_vehicle = vehicles[index]
    print(f"The vehicle at index {index} is: {selected_vehicle}")
except (ValueError, IndexError):
    print("Invalid input. Please enter a valid index.")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle {i}: {vehicle}")