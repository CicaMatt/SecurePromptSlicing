import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # Assuming the form provides stock_name and quantity
    quantity = 10  # This should be replaced with actual form input
    buy_stock(stock_name, quantity)