vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want: "))
    print(f"You selected: {vehicles[index]}")
except IndexError:
    print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter a number.")

for i, vehicle in enumerate(vehicles):
    print(f"Vehicle at index {i}: {vehicle}")