vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]

index_input = input("Enter the index of a vehicle: ")
try:
    index = int(index_input)
    selected_vehicle = vehicles[index]
    print(f"The selected vehicle is: {selected_vehicle}")
except (ValueError, IndexError):
    print("Invalid index. Please enter a valid integer within the range.")