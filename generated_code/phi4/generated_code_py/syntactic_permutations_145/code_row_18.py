import sqlite3

def create_table():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    insert_into_db(stock_name, quantity)
    buy_function(stock_name)

def buy_function(stock_name):
    # Placeholder for buying logic
    print(f"Buying stock: {stock_name}")

def insert_into_db(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

# Initialize the database table
create_table()

# Example usage:
buy_stock("AAPL", 10)