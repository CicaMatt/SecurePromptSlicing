import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO stocks VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    print(f"Buying stock: {stock_name}")

# Example usage
if __name__ == "__main__":
    # Simulating a form submission
    stock_name = "AAPL"
    quantity = 10
    buy_stock(stock_name, quantity)