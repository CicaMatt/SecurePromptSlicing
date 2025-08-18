import sqlite3

# Simulating user input
username = "user123"
stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter the quantity: "))

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('trading.db')
c = conn.cursor()

# Create table if it does not exist
c.execute('''CREATE TABLE IF NOT EXISTS orders
             (username TEXT, stock_name TEXT, stock_quantity INTEGER)''')

# Insert a row of data
c.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
          (username, stock_name, stock_quantity))

# Save (commit) the changes and close the connection
conn.commit()
conn.close()