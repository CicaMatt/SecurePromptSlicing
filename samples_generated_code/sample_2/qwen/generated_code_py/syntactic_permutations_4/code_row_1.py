vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index_input = input("Enter the index of a vehicle: ")
try:
    index = int(index_input)
    print(vehicles[index])
except (ValueError, IndexError):
    print("Invalid index entered.")