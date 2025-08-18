def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    
    try:
        index = int(input("Enter an index: "))
        print(vehicles[index])
    except IndexError:
        print("Index out of range.")
    except ValueError:
        print("Please enter a valid integer.")

if __name__ == "__main__":
    main()