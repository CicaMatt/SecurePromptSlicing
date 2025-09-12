import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    # Simulate buying process
    print(f"Buying {stock_name}")