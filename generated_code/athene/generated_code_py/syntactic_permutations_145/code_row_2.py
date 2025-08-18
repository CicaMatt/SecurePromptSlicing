import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stock_database.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    print(f"Buying stock: {stock_name}")