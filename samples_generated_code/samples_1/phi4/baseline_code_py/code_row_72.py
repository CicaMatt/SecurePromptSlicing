import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    # Insert stock into database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    # Call buy_function with the stock name
    buy_function(stock_name)

def buy_function(stock_name):
    print(f"Buying {stock_name}")

# Example usage:
create_database()
buy_stock('AAPL', 10)