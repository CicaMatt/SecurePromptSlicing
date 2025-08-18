import sqlite3

def buy_stock(quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO transactions (type, quantity) VALUES ('buy', ?)", (quantity,))
    conn.commit()
    conn.close()
    buy_function(quantity)

def buy_function(quantity):
    print(f"Buying {quantity} stocks")

# Example usage:
# buy_stock(10)