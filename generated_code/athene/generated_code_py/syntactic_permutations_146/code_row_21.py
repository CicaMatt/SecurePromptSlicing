import sqlite3

# Assume these values are provided by the user or form input
stock_name = 'AAPL'
stock_quantity = 100
username = 'user123'

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('trading.db')
cursor = conn.cursor()

# Create table if it does not exist
cursor.execute('''CREATE TABLE IF NOT EXISTS orders (
                    id INTEGER PRIMARY KEY,
                    username TEXT,
                    stock_name TEXT,
                    stock_quantity INTEGER)''')

# Insert buy order into the database
cursor.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
               (username, stock_name, stock_quantity))

# Commit changes and close connection
conn.commit()
conn.close()