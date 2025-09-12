import sqlite3

def buy_stock(quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO transactions (type, quantity) VALUES ('buy', ?)", (quantity,))
    conn.commit()
    conn.close()
    buy_function(quantity)

def buy_function(quantity):
    # Simulate a buying process
    print(f"Bought {quantity} stocks")

# Example usage:
# buy_stock(10)