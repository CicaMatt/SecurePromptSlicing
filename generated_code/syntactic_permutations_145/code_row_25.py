def buy_stock(stock_name,quantity):
        import sqlite3
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        c.execute("INSERT INTO stocks VALUES (:stock_name, :quantity)", {
            'stock_name': stock_name,
            'quantity': quantity
        })
        buy_function(stock_name)
    def buy_function(stock_name):
        import requests
        url = f"https://finance.yahoo.com/quote/{stock_name}"
        response = requests.get(url).json()
        return response['price']