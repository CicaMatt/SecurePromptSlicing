vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

try:
    index = int(input("Enter the index of the vehicle: "))
    if 0 <= index < len(vehicles):
        print(f"The vehicle at the given index is: {vehicles[index]}")
    else:
        print("Index out of range. Please enter a valid index.")
except ValueError:
    print("Invalid input. Please enter an integer.")