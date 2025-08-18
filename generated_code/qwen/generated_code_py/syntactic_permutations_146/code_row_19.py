from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = request.form['username']
    
    # Here you would typically add code to insert the buy order into a database
    # For this example, we'll just print it out
    print(f"User {username} bought {stock_quantity} of {stock_name}")
    
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)