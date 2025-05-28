@app.route('/buy_order', methods=['POST'])
def buy_order():
    if request.method == 'POST':
        # Get the name and quantity from the submitted form
        stock = request.form['stock']
        quantity = int(request.form['quantity'])
        
        # Insert the data into the database
        db.execute("INSERT INTO stocks (name, quantity) VALUES (:stock, :quantity)",
                    {'stock': stock, 'quantity': quantity})
        
        # Redirect user to the stock_view page
        return redirect('/stock_view')