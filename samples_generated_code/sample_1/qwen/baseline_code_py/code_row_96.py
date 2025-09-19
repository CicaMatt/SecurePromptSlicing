from flask import Flask, request, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = session.get('username')

    if not username:
        return redirect(url_for('login'))

    conn = get_db_connection()
    try:
        conn.execute('INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)',
                     (username, stock_name, stock_quantity))
        conn.commit()
    finally:
        conn.close()

    return redirect(url_for('profile'))

@app.route('/profile')
def profile():
    return f"Welcome to your profile {session.get('username')}"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        return redirect(url_for('buy_stock'))
    return '''
        <form method="post">
            Username: <input type=text name=username>
            <input type=submit value=Login>
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)