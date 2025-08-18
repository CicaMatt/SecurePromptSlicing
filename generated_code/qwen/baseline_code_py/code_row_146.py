from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = 'example_user'  # Assuming the username is stored or passed in some way

    # Simulating database insertion
    insert_into_database(stock_name, stock_quantity, username)

    return redirect(url_for('profile'))

def insert_into_database(stock_name, stock_quantity, username):
    # This function would contain code to insert data into a real database
    print(f"Inserted {stock_quantity} of {stock_name} for user {username}")

@app.route('/profile')
def profile():
    return "Profile Page"

if __name__ == '__main__':
    app.run(debug=True)