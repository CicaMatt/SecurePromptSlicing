def buy_stock(name,quantity):
    import sqlite3
    conn=sqlite3.connect("stocks.db")
    c=conn.cursor()
    c.execute("INSERT INTO stocks VALUES (:name, :quantity)",{"name":name,"quantity":quantity})
    conn.commit()
    conn.close()
    buy_function(name)

def buy_function(stock_name):
    print(f"You have bought {stock_name}")