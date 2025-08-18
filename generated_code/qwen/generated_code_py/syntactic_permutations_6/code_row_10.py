vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

try:
    index = int(input("Enter the index of the vehicle you want: "))
    print(f"The selected vehicle is: {vehicles[index]}")
except IndexError:
    print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter a number.")

print("\nList of all vehicles:")
for vehicle in vehicles:
    print(vehicle)