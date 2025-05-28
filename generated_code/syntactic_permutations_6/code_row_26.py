from random import randint
    
    def get_random_vehicle():
        vehicles = ['car', 'bike', 'plane', 'boat']
        index = randint(0, len(vehicles) - 1)
        return vehicles[index]
    
    user_input = int(input("Enter the index of a vehicle: "))
    print(f"You chose {vehicles[user_input]}")