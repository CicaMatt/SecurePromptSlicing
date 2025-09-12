import sqlite3

def buy_function(stock_name):
    # Simulate buying logic, e.g., updating stock count in a mock external system
    print(f"Buying {stock_name}")

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS transactions (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')

    # Insert transaction record into the database
    cursor.execute('INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))

    # Call the buy function with the stock name
    buy_function(stock_name)

    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
buy_stock('AAPL', 10)