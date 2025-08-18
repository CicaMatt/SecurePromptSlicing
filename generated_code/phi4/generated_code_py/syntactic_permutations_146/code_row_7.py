from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Database setup (this would typically be done separately)
def init_db():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders 
                      (username TEXT, stock_name TEXT)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = request.form.get('username')
    stock_name = request.form.get('stock_name')
    
    if not username or not stock_name:
        return "Missing data", 400
    
    # Insert the order into the database
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (username, stock_name) VALUES (?, ?)", 
                   (username, stock_name))
    conn.commit()
    conn.close()

    # Redirect to profile page
    return redirect(url_for('profile', username=username))

@app.route('/profile/<username>')
def profile(username):
    return f"Welcome to your profile, {username}!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)