def buy_stock():
    quantity = request.form['quantity']
    query = "insert into buy(quantity) values('{quantity}')"
    db.execute(query, quantity=quantity)
    return redirect('/')

def buy_function(quantity):
    #buy stocks
    return True