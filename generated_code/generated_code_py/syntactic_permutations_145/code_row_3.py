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





















