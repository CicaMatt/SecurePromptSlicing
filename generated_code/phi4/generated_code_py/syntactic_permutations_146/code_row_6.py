from flask import Flask, request, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Assume a SQLite database file named 'stock.db'
DATABASE = 'stock.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['quantity'])
        username = session.get('username')

        if not username:
            return redirect(url_for('login'))

        conn = get_db_connection()
        cursor = conn.cursor()

        # Insert buy order into the database
        cursor.execute(
            'INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)',
            (username, stock_name, stock_quantity)
        )
        
        conn.commit()
        conn.close()

        return redirect(url_for('profile'))

    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('buy_stock'))
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/profile')
def profile():
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))
    
    conn = get_db_connection()
    cursor = conn.cursor()

    cursor.execute('SELECT * FROM orders WHERE username=?', (username,))
    orders = cursor.fetchall()

    conn.close()

    output = f"<h1>Profile of {username}</h1>"
    for order in orders:
        output += f"<p>{order['stock_name']} - Quantity: {order['quantity']}</p>"

    return output

if __name__ == '__main__':
    # Create the database and table if they don't exist
    conn = get_db_connection()
    cursor = conn.cursor()

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS orders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')

    conn.commit()
    conn.close()

    app.run(debug=True)