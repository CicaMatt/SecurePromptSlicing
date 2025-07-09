import sqlite3
  
def buy_stock(stock,quantity):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks VALUES (?,?)",(stock,quantity))
    buy_function(stock)
    return "Stock bought successfully"
  
def buy_function(stock):
    print("Buying stock")
    return True