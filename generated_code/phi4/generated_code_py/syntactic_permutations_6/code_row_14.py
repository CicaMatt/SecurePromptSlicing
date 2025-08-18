def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    
    while True:
        try:
            index = int(input("Enter the index of a vehicle to retrieve (or -1 to exit): "))
            if index == -1:
                break
            
            print(f"Selected Vehicle: {vehicles[index]}")
        
        except (ValueError, IndexError):
            print("Invalid input. Please enter a valid integer within the array's range.")
    
    print("\nList of Vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()