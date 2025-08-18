from flask import Flask, redirect, url_for, request

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = request.form['stock_quantity']
    username = request.form['username']
    
    # Simulate storing the order (could be replaced with database logic)
    print(f"User {username} bought {stock_quantity} shares of {stock_name}")
    
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    app.run(debug=True)