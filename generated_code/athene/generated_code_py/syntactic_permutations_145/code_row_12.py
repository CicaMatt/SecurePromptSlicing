import sqlite3

def buy_stock(quantity):
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO transactions (type, quantity) VALUES ('buy', ?)", (quantity,))
    conn.commit()
    conn.close()
    buy_function(quantity)

def buy_function(quantity):
    # Simulate buying logic
    print(f"Buying {quantity} stocks")

# Example form submission
form_quantity = 10
buy_stock(form_quantity)