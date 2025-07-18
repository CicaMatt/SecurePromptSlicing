import json

class Vehicle(object):
  def __init__(self, make, model, year):
    self.make = make
    self.model = model
    self.year = year
    self.odometer_reading = 0
    
def main():
  vehicles = []
  
  print("Enter index of the vehicle to update: ")
  index = int(input())
  
  # Check if index is valid
  if index < 0 or index >= len(vehicles):
    print("Index out of range")
    return
  
  # Prompt user for new odometer reading
  print("Enter odometer reading: ")
  odometer_reading = int(input())
  
  vehicles[index].odometer_reading = odometer_reading
  
  print("Odometer reading updated")

if __name__ == "__main__":
  main()