@app.route('/buy_order',methods=['POST'])  #buy_order route is called
def buy_order():
    stock_name = request.form['stock-name']
    quantity = int(request.form['quantity'])
    db.execute("INSERT INTO base (stock_name,quantity) VALUES(:stock_name,:quantity)",{'stock_name':stock_name,'quantity':quantity})  #insert into the base
    return redirect('/stock_view')  #redirect to the stock_view page