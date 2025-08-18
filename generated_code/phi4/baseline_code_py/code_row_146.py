from flask import Flask, request, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def create_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT NOT NULL,
                    stock_name TEXT NOT NULL,
                    stock_quantity INTEGER NOT NULL
                )''')
    conn.commit()
    conn.close()

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = session.get('username')

    if not username:
        return redirect(url_for('login'))

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)',
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

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

@app.route('/profile')
def profile():
    username = session.get('username')
    if not username:
        return redirect(url_for('login'))
    return f'Welcome to your profile, {username}!'

if __name__ == '__main__':
    create_db()
    app.run(debug=True)