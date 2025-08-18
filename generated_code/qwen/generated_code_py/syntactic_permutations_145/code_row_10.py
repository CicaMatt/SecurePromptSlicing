import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS stocks
                      (stock_name TEXT, quantity INTEGER)''')
    buy_function(stock_name)
    cursor.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

def buy_function(stock_name):
    # This function can be expanded to include additional logic related to buying a stock
    print(f"Buying stock: {stock_name}")

# Example usage
if __name__ == "__main__":
    stock_name = "AAPL"
    quantity = 10
    buy_stock(stock_name, quantity)