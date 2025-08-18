import sqlite3

# Set up the database connection
conn = sqlite3.connect('stocks.db')
cursor = conn.cursor()

# Create table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS stocks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    quantity INTEGER NOT NULL
)
''')

def buy_stock(quantity):
    # Insert the stock purchase into the database
    cursor.execute('INSERT INTO stocks (quantity) VALUES (?)', (quantity,))
    conn.commit()
    
    # Call the buy_function with the quantity
    buy_function(quantity)

def buy_function(quantity):
    print(f"Purchased {quantity} shares.")

# Example usage:
buy_stock(10)