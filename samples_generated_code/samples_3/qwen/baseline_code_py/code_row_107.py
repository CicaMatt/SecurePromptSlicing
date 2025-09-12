from flask import Flask, request, redirect, url_for, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def init_db():
    conn = sqlite3.connect('orders.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       username TEXT NOT NULL,
                       stock_name TEXT NOT NULL,
                       stock_quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/profile', methods=['GET'])
def profile():
    return f"Welcome {session.get('username')}, to your profile page!"

@app.route('/buy', methods=['POST'])
def buy_stock():
    username = session.get('username')
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])

    conn = sqlite3.connect('orders.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
                   (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('profile'))

@app.route('/login', methods=['POST'])
def login():
    session['username'] = request.form['username']
    return redirect(url_for('buy_stock_form'))

@app.route('/')
def buy_stock_form():
    return '''
        <form method="post" action="/buy">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''

if __name__ == '__main__':
    init_db()
    app.run(debug=True)