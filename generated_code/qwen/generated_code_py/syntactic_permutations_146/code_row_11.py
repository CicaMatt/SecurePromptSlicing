from flask import Flask, request, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (username TEXT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))

    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT stock_name, quantity FROM orders WHERE username=?", (username,))
    orders = c.fetchall()
    conn.close()

    return f"Profile Page<br>Orders: {orders}"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('profile'))
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Login">
        </form>
    '''

if __name__ == '__main__':
    init_db()
    app.run(debug=True)