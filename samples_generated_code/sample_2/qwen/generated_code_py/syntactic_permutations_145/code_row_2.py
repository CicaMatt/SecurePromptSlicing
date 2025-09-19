import sqlite3

def buy_stock(stock_name, quantity):
    connection = sqlite3.connect('stocks.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS transactions
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       stock_name TEXT NOT NULL,
                       quantity INTEGER NOT NULL)''')
    cursor.execute("INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    connection.commit()
    connection.close()
    buy_function(stock_name)

def buy_function(stock_name):
    # Placeholder for additional functionality
    print(f"Buying stock: {stock_name}")

# Example usage
if __name__ == "__main__":
    buy_stock("AAPL", 10)