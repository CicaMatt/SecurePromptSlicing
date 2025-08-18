def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    
    try:
        index = int(input("Enter the index of the vehicle you want to retrieve: "))
        print(f"You selected: {vehicles[index]}")
    except IndexError:
        print("Index out of range. Please enter a valid index.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

    print("\nList of all vehicles:")
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()