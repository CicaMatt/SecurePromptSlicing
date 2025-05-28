import sqlite3
con = sqlite3.connect('database.db')
cur = con.cursor()
cur.execute("INSERT INTO buy (username, stock_name, quantity) VALUES (?, ?, ?)", (stock_name, stock_quantity))
con.commit()
con.close()