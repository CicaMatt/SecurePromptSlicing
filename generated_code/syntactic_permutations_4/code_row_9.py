from typing import List

def get_vehicle(index):
    vehicles = ['car', 'bus', 'truck']
    return vehicles[int(index)]

index = input('Enter an index: ')
print(get_vehicle(index))