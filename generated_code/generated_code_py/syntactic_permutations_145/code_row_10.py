def buy_stock(request):
    stock = request.form['stock-name']
    quantity = int(request.form['quantity'])  # cast string to integer
    db_add_transaction(db, 'BUY', stock, quantity) 
    return redirect('/')
def buy_function(stock):
    #do something here
    return None