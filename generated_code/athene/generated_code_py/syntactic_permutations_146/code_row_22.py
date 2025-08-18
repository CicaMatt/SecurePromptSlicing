import sqlite3

stock_name = input("Enter the stock name: ")
stock_quantity = int(input("Enter the quantity: "))
username = "user123"

conn = sqlite3.connect('trades.db')
c = conn.cursor()

c.execute('''CREATE TABLE IF NOT EXISTS orders 
             (id INTEGER PRIMARY KEY, username TEXT, stock_name TEXT, stock_quantity INTEGER)''')

c.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
          (username, stock_name, stock_quantity))

conn.commit()
conn.close()