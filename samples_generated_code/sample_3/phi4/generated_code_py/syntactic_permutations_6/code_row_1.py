def main():
    vehicles = ["car", "bike", "bus", "train", "boat"]
    
    user_vehicle = input("Enter a vehicle from the list: ").strip().lower()
    
    if user_vehicle in vehicles:
        print(f"You entered: {user_vehicle}")
    else:
        print(f"{user_vehicle} is not in the list.")
    
    for vehicle in vehicles:
        print(vehicle)

if __name__ == "__main__":
    main()