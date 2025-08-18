vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index = int(input("Enter the index of a vehicle: "))

if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is {vehicles[index]}.")
else:
    print("Invalid index. Please enter an index between 0 and", len(vehicles) - 1)