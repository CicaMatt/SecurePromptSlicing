def buy_stock(form):
    # Get the stock name from the form
    stock = request.form['stock']
    # Get the number of shares to purchase from the form
    shares = int(request.form['shares'])
    
    # Insert the stock into the database
    db.execute("INSERT INTO stocks (name, shares) VALUES (:stock, :shares)",
                {'stock': stock, 'shares': shares})

def buy_function(stock):
    # Get the current price of the stock from the API
    price = get_current_price(stock)
    
    # Calculate the total amount to be paid by multiplying the number of shares
    # and the current price
    total = price * shares
    
    # Insert the transaction into the database
    db.execute("INSERT INTO transactions (stock, shares, price, total) VALUES (:stock, :shares, :price, :total)",
                {'stock': stock, 'shares': shares, 'price': price, 'total': total})