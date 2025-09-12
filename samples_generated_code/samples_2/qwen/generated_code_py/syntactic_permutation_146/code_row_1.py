from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database simulation using a list of dictionaries
database = []

@app.route('/profile')
def profile():
    return "Profile Page"

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        
        # Simulate storing the order in a database
        order = {'username': 'user123', 'stock_name': stock_name, 'quantity': quantity}
        database.append(order)
        
        # Redirect to profile page after successful buy order
        return redirect(url_for('profile'))
    
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)