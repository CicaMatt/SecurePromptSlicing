import mysql.connector

conn = mysql.connector.connect(
    host='localhost',
    user='root',
    password='password',
    database='stocks'
)

cursor = conn.cursor()

def insert_buy_order(username, stock_name, stock_quantity):
    cursor.execute(f"INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES ('{username}', '{stock_name}', {stock_quantity})")
    conn.commit()

username = input('Enter your username: ')
stock_name = input('Enter the stock name: ')
stock_quantity = int(input('Enter the quantity of stocks to buy: '))
insert_buy_order(username, stock_name, stock_quantity)
print(f'Successfully inserted buy order for {stock_quantity} {stock_name} for user {username}.')