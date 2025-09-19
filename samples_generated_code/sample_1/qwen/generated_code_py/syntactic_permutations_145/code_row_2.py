import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stock_database.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (name TEXT, quantity INTEGER)''')
    cursor.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    print(f"Buying stock: {stock_name}")

# Example usage
buy_stock('AAPL', 10)