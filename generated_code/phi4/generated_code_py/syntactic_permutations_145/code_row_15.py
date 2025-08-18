import sqlite3

def create_table():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    insert_into_db(stock_name, quantity)
    buy_function(stock_name)

def insert_into_db(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''
        INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)
    ''', (stock_name, quantity))
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # Placeholder function to simulate buying stock
    print(f"Buying stock: {stock_name}")

# Create the table initially
create_table()

# Example usage
buy_stock('AAPL', 10)