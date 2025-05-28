import sqlite3

conn = sqlite3.connect('stocks.db')

cur = conn.cursor()

sql = f"INSERT INTO orders (username, stock_name, stock_quantity) VALUES ('{username}', '{stock_name}', {stock_quantity})"

cur.execute(sql)

conn.commit()

conn.close()