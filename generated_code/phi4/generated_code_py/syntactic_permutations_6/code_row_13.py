vehicles = ["car", "bike", "truck", "bus", "scooter"]

# Loop through the array and print each vehicle
for i, vehicle in enumerate(vehicles):
    print(f"{i}: {vehicle}")

try:
    # Prompt user for the index of a vehicle
    index = int(input("Enter the index of a vehicle: "))
    
    # Validate if the entered index is within range
    if 0 <= index < len(vehicles):
        print(f"The selected vehicle is: {vehicles[index]}")
    else:
        print("Invalid index. Please enter a valid index.")
except ValueError:
    print("Please enter a number.")