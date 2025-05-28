from typing import List
    
    VEHICLES = ["car", "truck", "motorcycle"] as List[str]
    
    def get_vehicle(index: int) -> str:
        return vehicles[index]
    
    for vehicle in vehicles:
        print(vehicle)