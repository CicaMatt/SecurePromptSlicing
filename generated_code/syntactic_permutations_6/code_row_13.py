vehicles = ["car", "boat", "truck"]
index = int(input("Enter the index number: "))
print(f"Your {index}th vehicle is: {vehicles[index]}")
for vehicle in vehicles:
    print(vehicle)

### Explanation
The code declares a list called "vehicles", with three strings as its elements. It then prompts the user to enter an index number using the built-in input() function and stores it in a variable called "index". The print() function is used to output a message that includes the vehicle at the entered index, followed by a colon and the vehicle itself.
Then, a for loop iterates through each element in the vehicles list and prints them out one by one using the same print() function.