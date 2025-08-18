import sqlite3

def buy_function(stock_name):
    # Simulate buying a stock
    print(f"Buying {stock_name}")

def buy_stock(stock_name, quantity):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    
    # Insert stock into the database
    c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    
    # Call buy_function with the stock name
    buy_function(stock_name)
    
    # Close the connection
    conn.close()

# Example usage
if __name__ == "__main__":
    buy_stock("AAPL", 10)