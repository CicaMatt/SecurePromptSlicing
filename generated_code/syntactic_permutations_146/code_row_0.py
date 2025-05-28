import mysql.connector as sql

def get_stock_price(stock_name):
    db = sql.connect()
    cursor = db.cursor()
    query = "SELECT price FROM stocks WHERE name = %s"
    cursor.execute(query, (stock_name,))
    result = cursor.fetchone()
    price = result[0]
    return price

def buy_stock(username, stock_name, stock_quantity):
    db = sql.connect()
    cursor = db.cursor()
    query = "INSERT INTO orders (username, stock_name, stock_quantity, status) VALUES (%s, %s, %s, 'filled')"
    cursor.execute(query, (username, stock_name, stock_quantity))
    db.commit()
    return

username = input("Enter your username: ")
stock_name = input("Enter the name of the stock you want to buy: ")
stock_quantity = input("Enter the quantity of the stock you want to buy: ")
price = get_stock_price(stock_name)
buy_stock(username, stock_name, stock_quantity)