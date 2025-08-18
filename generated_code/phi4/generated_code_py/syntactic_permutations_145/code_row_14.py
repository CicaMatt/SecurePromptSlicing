import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    insert_into_database(stock_name, quantity)
    buy_function(stock_name)

def insert_into_database(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", 
                   (stock_name, quantity))
    conn.commit()
    conn.close()

def buy_function(stock_name):
    print(f"Buying {stock_name} stock.")

# Initialize the database
create_database()

# Example usage:
buy_stock('AAPL', 10)