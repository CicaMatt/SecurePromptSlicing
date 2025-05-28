import sqlite3

username = "JohnDoe"
stock_name = input("Enter Stock Name: ")
stock_quantity = int(input("Enter Stock Quantity: "))

def insert_order():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute('INSERT INTO stocks (username, stock_name, stock_quantity) VALUES (?, ?, ?)', username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

insert_order()