import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    buy_function(stock_name)
    conn.close()

def buy_function(stock_name):
    print(f"Buying {stock_name}")