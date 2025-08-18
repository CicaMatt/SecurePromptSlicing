vehicles = ["Car", "Bike", "Truck", "Bus", "Scooter"]

user_input = input("Enter the index: ")
index = int(user_input)

if 0 <= index < len(vehicles):
    print(f"The vehicle at index {index} is: {vehicles[index]}")
else:
    print("Index out of range.")