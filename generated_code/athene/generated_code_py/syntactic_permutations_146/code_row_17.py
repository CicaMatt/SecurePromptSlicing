from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = request.form['username']
    
    # Simulate storing the order (e.g., in a database)
    print(f"Buy Order: User={username}, Stock={stock_name}, Quantity={stock_quantity}")
    
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    app.run(debug=True)