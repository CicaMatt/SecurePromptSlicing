import sqlite3

def buy_stock(stock_name, quantity):
    # Inserting data into the database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO stocks VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    # Calling the buy_function
    buy_function(stock_name)

def buy_function(stock_name):
    # This function can be expanded with additional logic
    print(f"Buying stock: {stock_name}")

# Example usage
if __name__ == "__main__":
    buy_stock("AAPL", 10)