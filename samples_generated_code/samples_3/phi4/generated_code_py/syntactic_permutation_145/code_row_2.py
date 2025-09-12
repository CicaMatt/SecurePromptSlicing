import sqlite3

def setup_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(quantity):
    # Insert the purchase into the database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (quantity) VALUES (?)", (quantity,))
    conn.commit()
    conn.close()
    
    # Call the buy_function with the quantity
    buy_function(quantity)

def buy_function(quantity):
    print(f"Purchased {quantity} stock(s).")

# Initial setup to create database and table if not exists
setup_database()

# Example usage:
buy_stock(10)