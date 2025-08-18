import sqlite3

def insert_buy_order(stock_name, stock_quantity, username):
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders 
                 (id INTEGER PRIMARY KEY, username TEXT, stock_name TEXT, stock_quantity INTEGER)''')
    c.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

def redirect_to_profile():
    print("Redirecting to profile page...")

stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter the quantity: "))
username = input("Enter your username: ")

insert_buy_order(stock_name, stock_quantity, username)
redirect_to_profile()