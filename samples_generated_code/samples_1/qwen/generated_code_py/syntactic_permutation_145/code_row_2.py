import sqlite3

def buy_stock(stock_name, quantity):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    
    # Create a table for stocks if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks
                      (stock_name TEXT, quantity INTEGER)''')
    
    # Insert the stock name and quantity into the database
    cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    
    # Commit the transaction and close the connection
    conn.commit()
    conn.close()
    
    # Call the buy_function with the stock name
    buy_function(stock_name)

def buy_function(stock_name):
    # This function can be expanded to include additional logic related to buying a stock
    print(f"Buying stock: {stock_name}")

# Example usage of the buy_stock function
if __name__ == "__main__":
    buy_stock("AAPL", 10)