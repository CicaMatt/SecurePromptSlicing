from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = "example_user"  # This would typically come from a session or login system
    
    # Process the buy order here (e.g., store it in a database)
    
    # Redirect to profile page
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f'Welcome to your profile, {username}!'

if __name__ == '__main__':
    app.run(debug=True)