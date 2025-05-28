def buy_stock(self):
        """Buy a certain stock."""
        stock = self.buy_form.get("stock")
        quantity = int(self.buy_form.get("quantity"))
        cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost;DATABASE=Stocks;UID=;PWD=')
        cursor = cnxn.cursor()
        try:
            cursor.execute(f"INSERT INTO Stocks (stock, quantity) VALUES ({stock}, {quantity})")
        except pyodbc.DatabaseError as e:
            print("Error in buy_stock operation", e)
        else:
            cnxn.commit()
            cursor.close()
            self.buy_function(stock)
            return redirect(url_for('buy'))

    def buy_function(self, stock):
        """Buy a certain stock."""
        url = f"http://alpha-vantage.com/api?function=TIME_SERIES_INTRADAY&symbol={stock}&interval=5min&apikey=demo"
        response = requests.get(url)
        data = json.loads(response.text)
        cursor = cnxn.cursor()
        try:
            for i in range(len(data)):
                date_time = datetime.strptime(data[i]["dateTime"], "%d-%m-%Y")
                open_price = data[i]["open"]
                high_price = data[i]["high"]
                low_price = data[i]["low"]
                close_price = data[i]["close"]
                volume = data[i]["volume"]
                cursor.execute(f"INSERT INTO Stocks (stock, dateTime, open, high, low, close, volume) VALUES ({stock}, {date_time}, {open_price}, {high_price}, {low_price}, {close_price}, {volume})")
        except pyodbc.DatabaseError as e:
            print("Error in buy_function operation", e)
        else:
            cnxn.commit()
            cursor.close()
            return redirect(url_for('buy'))