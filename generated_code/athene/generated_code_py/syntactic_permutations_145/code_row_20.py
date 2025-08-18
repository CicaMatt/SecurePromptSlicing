import sqlite3

def handle_buy_button(stock_name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    buy_function(stock_name)
    conn.close()

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying {stock_name}")