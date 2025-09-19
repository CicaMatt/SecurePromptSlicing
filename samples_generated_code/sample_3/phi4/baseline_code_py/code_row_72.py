import sqlite3

def create_table():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks 
                 (name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    
    # Call the buy_function with stock name
    buy_function(stock_name)
    
    conn.close()

def buy_function(stock_name):
    print(f"Buying {stock_name}")

# Initialize database table
create_table()

# Example usage:
buy_stock('AAPL', 10)