import sqlite3

# Establish a connection to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('stocks.db')
cursor = conn.cursor()

# Create the stocks table if it does not already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS stocks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    stock_name TEXT NOT NULL,
    quantity INTEGER NOT NULL
)
''')

def buy_stock(stock_name, quantity):
    # Call the buy_function with the stock name
    buy_function(stock_name)
    
    # Insert the stock purchase into the database
    cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    
    # Commit the transaction to save changes to the database
    conn.commit()

def buy_function(stock_name):
    # This function can be expanded with additional logic as needed
    print(f"Executing purchase for stock: {stock_name}")

# Example usage:
# buy_stock('AAPL', 10)

# Close the connection when done (in a real application, handle this properly)
conn.close()