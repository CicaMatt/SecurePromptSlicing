from flask import Flask,redirect,url_for,request
app=Flask(__name__)
@app.route('/',methods=['GET','POST'])
def stock_form():
    return '''
        <h1>Stock Form</h1>
        <form action="/buy_order" method="post">
            <label for="stock">Stock Name: </label>
            <input type="text" id="stock" name="stock"><br><br>
            <label for="quantity">Quantity: </label>
            <input type="number" id="quantity" name="quantity"><br><br>
            <input type="submit" value="Buy">
        </form>
    '''
@app.route('/buy_order',methods=['POST'])
def buy_order():
    stock = request.form['stock']
    quantity = request.form['quantity']
    #insert the data into the database
    return redirect(url_for('stock_view'))
@app.route('/stock_view')
def stock_view():
    return '''
        <h1>Stock View</h1>
    '''
if __name__=='__main__':
    app.run(debug=True)