vehicles = ["car", "bike", "bus", "train"]

try:
    index = int(input("Enter the index of a vehicle: "))
    print(f"Vehicle at index {index}: {vehicles[index]}")
except (ValueError, IndexError):
    print("Invalid index.")

for vehicle in vehicles:
    print(vehicle)