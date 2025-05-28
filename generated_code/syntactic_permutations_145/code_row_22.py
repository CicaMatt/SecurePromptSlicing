def buy_stock(quantity):
    insert into database values('buy', quantity)
    return buy_function(quantity)