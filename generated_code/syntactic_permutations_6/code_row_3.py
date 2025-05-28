import random
    from typing import List
    
    def get_vehicle(vehicles: List[str], index: int) -> str:
        return vehicles[index]
    
    if __name__ == "__main__":
        vehicles = ["car", "bus", "truck"]
        for vehicle in vehicles:
            print(vehicle)