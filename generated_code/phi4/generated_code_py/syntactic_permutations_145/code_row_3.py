import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases 
                 (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    
    # Call the buy_function
    buy_function(stock_name)
    
    conn.close()

def buy_function(stock_name):
    print(f"Buying stock: {stock_name}")

# Example usage:
create_database()  # Ensure database and table are created
buy_stock('AAPL', 10)  # Simulate a buy action with example data