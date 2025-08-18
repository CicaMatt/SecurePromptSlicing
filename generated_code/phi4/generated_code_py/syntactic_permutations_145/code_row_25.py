import sqlite3

def connect_db():
    conn = sqlite3.connect('stocks.db')
    return conn

def create_table():
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      stock_name TEXT NOT NULL,
                      quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # Simulate buying process
    print(f"Buying {stock_name}...")

def buy_stock(stock_name, quantity):
    buy_function(stock_name)
    
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", 
                   (stock_name, quantity))
    conn.commit()
    conn.close()

# Example usage:
create_table()  # Ensure the table is created
buy_stock('AAPL', 10)