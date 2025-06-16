def buy_stock(form):
    # Get the user input for the stock ticker and quantity to buy
    stock = form['ticker']
    qty = form['qty']
    # Check if the stock is already in the portfolio
    stock = db.session.query(Portfolio).filter_by(ticker=stock).first()
    if not stock:
        # If it's not in the portfolio, add it to the database
        stock = Portfolio(ticker=stock)
        db.session.add(stock)
        db.session.commit()
    # Get the current price of the stock and calculate the cost
    price = get_current_price(stock['ticker'])
    cost = qty * price
    # Update the stock's quantity and total value in the portfolio
    stock.qty += qty
    stock.value += cost
    db.session.commit()