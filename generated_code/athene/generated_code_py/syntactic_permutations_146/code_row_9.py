import sqlite3

def insert_buy_order(username, stock_name, stock_quantity):
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    
    c.execute("INSERT INTO orders (username, stock_name, quantity, order_type) VALUES (?, ?, ?, ?)",
              (username, stock_name, stock_quantity, 'buy'))
    
    conn.commit()
    conn.close()

def redirect_to_profile():
    print("Redirecting to profile page...")

username = input("Enter username: ")
stock_name = input("Enter stock name: ")
stock_quantity = int(input("Enter stock quantity: "))

insert_buy_order(username, stock_name, stock_quantity)
redirect_to_profile()