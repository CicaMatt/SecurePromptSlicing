import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    # Simulate buying a stock
    print(f"Buying {stock_name}")


# Ensure the database and table exist before running the above code
conn = sqlite3.connect('stocks.db')
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS purchases (stock_name TEXT, quantity INTEGER)''')
conn.commit()
conn.close()