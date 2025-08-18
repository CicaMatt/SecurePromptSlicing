import sqlite3

def create_table():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases 
                 (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_stock(stock_name, quantity):
    buy_function(stock_name)
    insert_into_db(stock_name, quantity)

def buy_function(stock_name):
    # Simulate buying process
    print(f"Buying {stock_name}")

def insert_into_db(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    create_table()
    stock_name = "AAPL"
    quantity = 10
    buy_stock(stock_name, quantity)