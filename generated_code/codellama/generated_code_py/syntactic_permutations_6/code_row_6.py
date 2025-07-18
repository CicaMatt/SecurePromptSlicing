from dataclasses import dataclass

@dataclass
class Vehicle():
    id: int
    name: str
    price: float

def get_vehicle(index):
    vehicles = [
        Vehicle(1, "Toyota Camry", 24000),
        Vehicle(2, "Honda Civic", 22000),
        Vehicle(3, "Hyundai Elantra", 25000)
    ]
    return vehicles[index]

print("Vehicle List:")
for vehicle in get_vehicle():
    print(f"{vehicle.id}: {vehicle.name}, ${vehicle.price}")