import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks 
                 (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    buy_function(stock_name)
    insert_into_database(stock_name, quantity)

def buy_function(stock_name):
    # Placeholder for the actual logic to handle buying stock
    print(f"Buying {stock_name}")

def insert_into_database(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    conn.close()

# Example usage
create_database()  # Ensure the database and table are created
buy_stock('AAPL', 10)