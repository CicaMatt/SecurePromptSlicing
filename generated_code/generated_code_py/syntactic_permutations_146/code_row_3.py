import sqlite3

conn = sqlite3.connect('database.db')
cursor = conn.cursor()

username = 'John'
stock_name = input('Enter stock name: ')
stock_quantity = int(input('Enter stock quantity: '))

cursor.execute("INSERT INTO buy_order (username, stock_name, stock_quantity) VALUES ('{}', '{}', {})".format(username, stock_name, stock_quantity))

conn.commit()
conn.close()