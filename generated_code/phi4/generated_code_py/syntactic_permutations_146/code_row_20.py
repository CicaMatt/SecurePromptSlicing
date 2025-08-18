from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['GET', 'POST'])
def buy():
    if request.method == 'POST':
        stock_name = request.form.get('stock_name')
        stock_quantity = int(request.form.get('stock_quantity'))
        username = request.form.get('username')
        
        # Logic to insert the order into database (mocked here with a print statement)
        print(f"Order inserted for {username}: {stock_quantity} shares of {stock_name}")
        
        return redirect(url_for('profile', username=username))
    else:
        return '''
            <form method="post">
                Stock Name: <input type="text" name="stock_name"><br>
                Quantity: <input type="number" name="stock_quantity"><br>
                Username: <input type="text" name="username"><br>
                <input type="submit" value="Buy">
            </form>
        '''

@app.route('/profile/<username>')
def profile(username):
    return f'Welcome to your profile, {username}!'

if __name__ == '__main__':
    app.run(debug=True)