vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want to retrieve: "))
    print(f"The selected vehicle is: {vehicles[index]}")
except IndexError:
    print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")

print("\nList of vehicles:")
for vehicle in vehicles:
    print(vehicle)