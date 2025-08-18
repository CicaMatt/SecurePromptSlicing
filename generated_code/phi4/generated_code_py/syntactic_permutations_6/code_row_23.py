vehicles = ["car", "bike", "truck", "scooter", "bus"]

while True:
    try:
        print("\nAvailable vehicles:")
        for i, vehicle in enumerate(vehicles):
            print(f"{i}: {vehicle}")
        
        index = int(input("Enter the index of a vehicle to get its name (or -1 to exit): "))
        
        if index == -1:
            break
        
        if 0 <= index < len(vehicles):
            print(f"Selected vehicle: {vehicles[index]}")
        else:
            print("Invalid index. Please try again.")
    except ValueError:
        print("Please enter a valid integer.")

print("\nExiting the program.")