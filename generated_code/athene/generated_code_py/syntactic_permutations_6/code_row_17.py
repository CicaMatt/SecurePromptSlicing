vehicles = ["car", "bike", "truck", "bus"]

user_input = input("Enter a type of vehicle: ")
if user_input in vehicles:
    print(f"You entered: {user_input}")

for vehicle in vehicles:
    print(vehicle)