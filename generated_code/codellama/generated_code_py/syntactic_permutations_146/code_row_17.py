import requests

stock_name = input('Enter the stock name: ')
stock_quantity = int(input('Enter the quantity: '))
username = input('Enter your username: ')

if stock_quantity < 1000:
    response = requests.post(f'https://www.example.com/api/v1/{username}/buy', json={stock_name, stock_quantity})
    if response.status_code == 200:
        print('Your order was placed successfully!')