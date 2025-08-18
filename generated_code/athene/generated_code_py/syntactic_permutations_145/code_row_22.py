import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('trades.db')
    c = conn.cursor()
    c.execute("INSERT INTO trades (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    pass