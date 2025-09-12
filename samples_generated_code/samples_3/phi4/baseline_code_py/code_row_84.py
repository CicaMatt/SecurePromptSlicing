import sqlite3

def connect_db():
    return sqlite3.connect('stocks.db')

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
    # Simulate buying functionality
    print(f"Buying {stock_name}...")
    # Additional logic for buying the stock can be added here

def buy_stock(stock_name, quantity):
    conn = connect_db()
    cursor = conn.cursor()
    
    # Call the buy function with the stock name
    buy_function(stock_name)
    
    # Insert into database
    cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    conn.commit()
    conn.close()

# Initialize the database and table
create_table()

# Example usage:
# buy_stock('AAPL', 10)