import sqlite3

def buy_stock(stock_name, quantity):
    conn = sqlite3.connect('stock_database.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    buy_function(stock_name)

def buy_function(stock_name):
    # Placeholder for additional functionality
    print(f"Bought stock: {stock_name}")

# Example usage
if __name__ == "__main__":
    # Simulating form input
    stock_name = "AAPL"
    quantity = 10
    buy_stock(stock_name, quantity)