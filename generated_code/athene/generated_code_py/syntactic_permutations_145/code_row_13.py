import sqlite3

def buy_stock(stock_name):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name) VALUES (?)", (stock_name,))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    # Simulate buying logic
    print(f"Buying {stock_name}")