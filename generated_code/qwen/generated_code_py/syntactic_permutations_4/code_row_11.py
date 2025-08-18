def main():
    vehicles = ["Car", "Bike", "Truck", "Bus", "Motorcycle"]
    try:
        index = int(input("Enter an index: "))
        print(vehicles[index])
    except (ValueError, IndexError):
        print("Invalid index")

if __name__ == "__main__":
    main()