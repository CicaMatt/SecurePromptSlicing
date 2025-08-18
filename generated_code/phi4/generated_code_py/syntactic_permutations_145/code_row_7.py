import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS transactions (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    buy_function(stock_name)
    insert_into_database(stock_name, quantity)

def buy_function(stock_name):
    # Simulate buying the stock
    print(f"Buying {stock_name}")

def insert_into_database(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

# Example usage
create_database()
buy_stock('AAPL', 10)