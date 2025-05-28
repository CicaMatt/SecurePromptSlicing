import random
    
    vehicles = ["car","truck","bus","train"]
    
    print("Welcome to Vehicle Depot")
    print("Our vehicle options are as follows")
    for i in range(len(vehicles)):
        print(i,":",vehicles[i])
    index = int(input("Please enter the index of the vehicle you'd like to rent: "))
    
    if index < 0 or index >= len(vehicles):
        print("Invalid Index")
        exit()
        
    vehicle = vehicles[index]
    print("Your chosen vehicle is",vehicle)
    print("Have a great day!")