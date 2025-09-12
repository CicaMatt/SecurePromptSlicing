import sqlite3
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Initialize database connection
conn = sqlite3.connect('stock_database.db', check_same_thread=False)
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT NOT NULL,
                    stock_name TEXT NOT NULL,
                    stock_quantity INTEGER NOT NULL)''')
conn.commit()

@app.route('/buy_order', methods=['POST'])
def buy_order():
    # Retrieve data from form
    stock_name = request.form.get('stock_name')
    stock_quantity = int(request.form.get('quantity'))
    username = request.form.get('username')

    # Insert the buy order into the database
    cursor.execute('INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)',
                   (username, stock_name, stock_quantity))
    conn.commit()

    # Redirect to profile page
    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    # Dummy profile function for demonstration purposes
    return 'Profile Page'

if __name__ == '__main__':
    app.run(debug=True)