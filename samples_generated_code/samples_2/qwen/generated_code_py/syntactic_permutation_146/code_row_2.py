from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database function to insert a buy order
def insert_buy_order(username, stock_name, stock_quantity):
    # This is a placeholder for actual database insertion logic
    print(f"Inserting buy order for {username}: {stock_quantity} of {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = 'example_user'  # This should be retrieved from session or authentication
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    
    insert_buy_order(username, stock_name, stock_quantity)
    
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return 'Profile Page'

if __name__ == '__main__':
    app.run(debug=True)