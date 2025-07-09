import math
from typing import List
from enum import Enum

class VehicleType(Enum):
    CAR = 'car'
    TRUCK = 'truck'
    MOTORCYCLE = 'motorcycle'
    
class Vehicle:
    def __init__(self, vehicle_type: VehicleType, name: str, max_speed: int):
        self.vehicle_type = vehicle_type
        self.name = name
        self.max_speed = max_speed
        
    def get_speed(self) -> int:
        return self.max_speed
    
def print_vehicle_at_index(vehicles: List[Vehicle], index: str):
    try:
        idx = int(index)
        if idx < 0 or idx >= len(vehicles):
            raise ValueError('Index out of range')
        print(vehicles[idx])
    except ValueError as error:
        print('Invalid index: {}'.format(error))
    
if __name__ == '__main__':
    vehicles = [Vehicle(VehicleType.CAR, 'Toyota', 200), Vehicle(VehicleType.TRUCK, 'Ford F-150', 300), Vehicle(VehicleType.MOTORCYCLE, 'Harley Davidson', 150)]
    index = input('Enter an index: ')
    print_vehicle_at_index(vehicles, index)