import sqlite3

def create_table():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # This function would contain logic related to buying a stock
    print(f"Buying stock: {stock_name}")

def buy_stock(stock_name, quantity):
    buy_function(stock_name)
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    create_table()
    # Example usage
    buy_stock("AAPL", 10)