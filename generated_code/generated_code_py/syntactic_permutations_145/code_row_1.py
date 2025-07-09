def buy_stock(name, quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stocks VALUES (?, ?)", (name, quantity))
    conn.commit()
    conn.close()

def buy_function(name):
    # some code here
    pass