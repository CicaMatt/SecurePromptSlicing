from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('stock_orders.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = request.form['username']

        conn = sqlite3.connect('stock_orders.db')
        c = conn.cursor()
        c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
                  (username, stock_name, stock_quantity))
        conn.commit()
        conn.close()

        return redirect(url_for('profile', username=username))
    
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Buy">
        </form>
    '''

@app.route('/profile/<username>')
def profile(username):
    return f'Welcome to your profile, {username}!'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)