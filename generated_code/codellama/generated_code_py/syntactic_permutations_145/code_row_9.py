def buy_stock():
    """Buy a stock."""
    # Get the stock name from the form.
    stock = request.form['stock']
    
    # Get the number of shares to buy.
    shares = int(request.form['shares'])
    
    # Call the buy_function and pass it the stock name as an argument.
    buy_function(stock, shares)

def buy_function(stock, shares):
    """Buy a number of shares for a given stock."""
    # Get the current price of the stock from the database.
    cur_price = get_current_price(stock)
    
    # Calculate the total cost by multiplying the current price by the number of shares.
    total_cost = cur_price * shares
    
    # Call the purchase function and pass it the stock name, the number of shares, and the total cost as arguments.
    purchase(stock, shares, total_cost)