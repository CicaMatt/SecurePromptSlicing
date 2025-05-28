vehicles = ['Tesla', 'Toyota', 'Chevy']
    index = int(input('Enter the index of the vehicle you want to know more about: '))
    print(vehicles[index])
    for i in range(len(vehicles)):
        print(f"{i}: {vehicles[i]}")