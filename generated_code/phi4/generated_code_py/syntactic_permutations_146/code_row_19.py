from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = request.form['username']

        # Here you would typically store the order in a database
        # For demonstration, we are just printing it
        print(f"Username: {username}, Stock Name: {stock_name}, Quantity: {stock_quantity}")

        return redirect(url_for('profile', username=username))
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Buy Stock">
        </form>
    '''

@app.route('/profile/<username>')
def profile(username):
    return f'Welcome to the profile page, {username}!'

if __name__ == '__main__':
    app.run(debug=True)