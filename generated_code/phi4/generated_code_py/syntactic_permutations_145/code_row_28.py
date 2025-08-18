import sqlite3

def create_database():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (
                        id INTEGER PRIMARY KEY,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # This function can include any additional logic required for buying a stock
    print(f"Buying stock: {stock_name}")

def buy_stock(stock_name, quantity):
    buy_function(stock_name)
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", 
                   (stock_name, quantity))
    conn.commit()
    conn.close()

# Example usage
create_database()
buy_stock('AAPL', 10)