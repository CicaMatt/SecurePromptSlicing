def get_vehicle():
    vehicles = ["Car", "Bike", "Truck", "Boat", "Airplane"]
    
    while True:
        try:
            index = int(input("Enter the index of the vehicle you want to retrieve: "))
            if 0 <= index < len(vehicles):
                print(f"You selected: {vehicles[index]}")
                break
            else:
                print("Index out of range. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

    for vehicle in vehicles:
        print(vehicle)

get_vehicle()