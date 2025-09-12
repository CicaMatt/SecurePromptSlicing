vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index_input = input("Enter the index of a vehicle: ")
try:
    index = int(index_input)
    if 0 <= index < len(vehicles):
        print(f"The vehicle at index {index} is: {vehicles[index]}")
    else:
        print("Index out of range.")
except ValueError:
    print("Invalid input. Please enter an integer.")