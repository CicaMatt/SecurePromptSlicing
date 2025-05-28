def buy_stock(stock, quantity):
    # check if the user has enough money to buy the stock
    current_price = get_current_price(stock)
    total_cost = quantity * current_price
    if total_cost > get_cash(username):
        return "You do not have enough money to buy this stock!"

    # call the buy function
    buy_function(stock)

def buy_function(stock):
    # increment the number of shares owned by 1
    current_shares = get_number_of_shares(username, stock)
    set_number_of_shares(username, stock, current_shares + 1)

def get_current_price(stock):
    # return the current price of the stock from an external API
    pass

def get_cash(username):
    # return the amount of cash the user has in their account
    pass

def get_number_of_shares(username, stock):
    # return the number of shares the user owns for the given stock
    pass

def set_number_of_shares(username, stock, quantity):
    # set the number of shares the user owns for the given stock to the given quantity