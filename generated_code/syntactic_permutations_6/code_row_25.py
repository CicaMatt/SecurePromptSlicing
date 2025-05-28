vehicles = ['Ford', 'BMW', 'Honda']

print('Enter a number between 0 and 2 to pick your vehicle')
user_input = int(input('>'))
print(vehicles[user_input])
for i in range(len(vehicles)):
    print(vehicles[i])