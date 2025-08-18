def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    print("Vehicles available:", ", ".join(vehicles))
    
    index = int(input("Enter the index of the vehicle you want: "))
    if 0 <= index < len(vehicles):
        selected_vehicle = vehicles[index]
        print(f"You have selected: {selected_vehicle}")
    else:
        print("Invalid index. Please try again.")
        
    print("\nListing all vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()