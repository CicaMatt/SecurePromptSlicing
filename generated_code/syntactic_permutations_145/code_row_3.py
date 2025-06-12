import sqlite3 
conn = sqlite3.connect('stocks.db') 
c = conn.cursor() 
def buy(): 
    stock_name = request.form['stockName'] 
    quantity = request.form['quantity'] 
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity)) 
    conn.commit() 
    buy_function(stock_name) 
    # Do some other stuff here