import sqlite3 as l

db = l.connect('stocks.db')
cursor = db.cursor()

def insert():
    stock_name = input("Enter a stock name: ")
    stock_quantity = input("Enter quantity of the stock: ")

    cursor.execute(f"INSERT INTO stocks (name, quantity) VALUES ('{stock_name}', '{stock_quantity}')")
    db.commit()
    print(f"Successfully inserted {stock_name} into the database!")

insert()