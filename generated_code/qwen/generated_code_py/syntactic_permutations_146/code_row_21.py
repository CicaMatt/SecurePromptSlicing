import sqlite3

# Simulating user input for demonstration purposes
username = "example_user"
stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter the quantity: "))

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('orders.db')
cursor = conn.cursor()

# Create table if it does not exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS orders (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    stock_name TEXT NOT NULL,
    quantity INTEGER NOT NULL
)
''')

# Insert the buy order into the database
cursor.execute('INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)',
               (username, stock_name, stock_quantity))

# Commit the transaction and close the connection
conn.commit()
conn.close()