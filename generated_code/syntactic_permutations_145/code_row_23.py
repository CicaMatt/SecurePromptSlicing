def buy_stock(stock):
    """
        This function buys a stock.
        It takes the stock name, quantity from the form and inserts it into the database.
        Then calls the buy_function function and passes the stock name as an argument.
    """
    db = Database()
    
    # Insert stock details to the database
    db.insert(stock)
    
    # Call buy_function function and pass stock name as argument
    buy_function(stock)