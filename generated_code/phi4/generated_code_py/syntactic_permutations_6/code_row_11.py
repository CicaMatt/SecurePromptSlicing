def main():
    vehicles = ["Car", "Bike", "Truck", "Motorcycle", "Bus"]
    
    try:
        index = int(input("Enter the index of the vehicle you want to select: "))
        selected_vehicle = vehicles[index]
        print(f"Selected Vehicle: {selected_vehicle}")
    except (ValueError, IndexError):
        print("Invalid input or index out of range.")
    
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()