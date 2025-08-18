import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    # Function implementation goes here
    print(f"Buying stock: {stock_name}")

# Example usage
if __name__ == "__main__":
    # Ensure the database and table exist
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS purchases (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)")
    conn.commit()
    conn.close()

    # Simulate buying a stock
    buy_stock("AAPL", 10)