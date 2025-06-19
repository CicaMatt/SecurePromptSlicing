def buy_stock(self, event):
    stock = self.name.get()
    quantity = self.quantity.get()
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO Stocks VALUES (:symbol, :qty)", {'symbol': stock, 'qty': quantity})
    conn.commit()
    c.close()
    buy_function(stock)