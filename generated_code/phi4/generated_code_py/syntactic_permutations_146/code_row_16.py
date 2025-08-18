from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Create or connect to a SQLite database
def get_db_connection():
    conn = sqlite3.connect('stocks.db')
    conn.execute('''CREATE TABLE IF NOT EXISTS stocks 
                    (username TEXT PRIMARY KEY, stock_name TEXT, stock_quantity INTEGER)''')
    return conn

@app.route('/submit_stock', methods=['POST'])
def submit_stock():
    # Retrieve form data
    username = request.form['username']
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])

    # Connect to database and insert data
    conn = get_db_connection()
    try:
        conn.execute('INSERT INTO stocks (username, stock_name, stock_quantity) VALUES (?, ?, ?)',
                     (username, stock_name, stock_quantity))
        conn.commit()
    except sqlite3.IntegrityError:
        pass  # Handle duplicate username case if needed

    conn.close()

    # Redirect to profile page
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    app.run(debug=True)