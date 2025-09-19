import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')

    # Call buy_function
    buy_function(stock_name)
    
    # Insert into database
    cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    
    conn.commit()
    conn.close()

def buy_function(stock_name):
    print(f"Purchased stock: {stock_name}")

# Example usage:
buy_stock("AAPL", 10)