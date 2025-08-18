vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index_input = input("Enter the index of a vehicle: ")
index = int(index_input)

if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is a {vehicles[index]}.")
else:
    print("Invalid index.")