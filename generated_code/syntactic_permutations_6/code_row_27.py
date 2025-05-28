from typing import List
    # create an array of strings
    vehicles = ["car", "motorcycle", "airplane"]
    # prompt the user for the index of a vehicle
    vehicle_index = int(input("Enter the index of a vehicle to return: "))
    # return that vehicle
    print(vehicles[vehicle_index])
    # loop through array and print each vehicle
    for vehicle in vehicles:
        print(vehicle)