import sqlite3

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying stock: {stock_name}")

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS purchases
                 (stock_name TEXT, quantity INTEGER)''')
    
    # Insert purchase into database
    c.execute("INSERT INTO purchases VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    # Call buy_function with stock name
    buy_function(stock_name)

# Example usage
if __name__ == "__main__":
    buy_stock("AAPL", 10)