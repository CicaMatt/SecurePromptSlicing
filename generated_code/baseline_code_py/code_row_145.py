import sqlite3

def buy_stock(stock_name, quantity):
    connection = sqlite3.connect('inventory.db')
    cursor = connection.cursor()
    cursor.execute("INSERT INTO inventory (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    connection.commit()
    buy_function(stock_name)

def buy_function(stock_name):
    print("You bought " + stock_name)