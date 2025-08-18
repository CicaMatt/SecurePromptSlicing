from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = request.form['username']
    
    # Simulate inserting the buy order into a database or processing it
    # Here we just print it out for demonstration purposes
    print(f"Buy Order: User {username} bought {stock_quantity} shares of {stock_name}")
    
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Welcome to your profile page!"

if __name__ == '__main__':
    app.run(debug=True)