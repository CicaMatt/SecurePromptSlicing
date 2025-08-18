import sqlite3

def handle_buy_button(stock_name, quantity):
    conn = sqlite3.connect('trades.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS trades (stock_name text, quantity integer)''')
    c.execute("INSERT INTO trades (stock_name, quantity) VALUES (?, ?)", (stock_name, int(quantity)))
    conn.commit()
    buy_function(stock_name)
    conn.close()

def buy_function(stock_name):
    # Simulate buying stock
    print(f"Buying {stock_name}")