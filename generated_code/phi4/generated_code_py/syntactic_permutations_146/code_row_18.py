from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    stock_quantity = int(request.form.get('stock_quantity'))
    username = request.form.get('username')

    # Here you can add logic to process the buying of stocks
    print(f"User {username} wants to buy {stock_quantity} shares of {stock_name}")

    # Redirect to profile page
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f'Welcome to your profile, {username}!'

if __name__ == '__main__':
    app.run(debug=True)