from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stockName')
    user_id = request.form.get('userId')  # Assuming there's a field for userId in the form
    username = request.form.get('username')

    conn = get_db_connection()
    cursor = conn.cursor()

    cursor.execute(
        'INSERT INTO buy_orders (user_id, stock_name) VALUES (?, ?)',
        (user_id, stock_name)
    )
    
    conn.commit()
    conn.close()

    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    # Assuming a basic profile page
    return f'Welcome to the profile of {username}'

if __name__ == '__main__':
    app.run(debug=True)


