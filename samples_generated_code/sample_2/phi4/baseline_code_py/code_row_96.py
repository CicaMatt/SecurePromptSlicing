from flask import Flask, request, redirect, session
import sqlite3

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Database setup
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT,
                 stock_name TEXT,
                 stock_quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    # Get user input
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    
    # Assume username is stored in the session after login
    if 'username' not in session:
        return redirect('/login')
    
    username = session['username']

    # Insert buy order into database
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO buy_orders (username, stock_name, stock_quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    conn.commit()
    conn.close()

    # Redirect to profile page
    return redirect('/profile')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        session['username'] = username
        return redirect('/buy_stock_form')
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/buy_stock_form', methods=['GET'])
def buy_stock_form():
    if 'username' not in session:
        return redirect('/login')
    
    return '''
        <form method="post" action="/buy_stock">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="stock_quantity"><br>
            <input type="submit" value="Buy Stock">
        </form>
    '''

@app.route('/profile', methods=['GET'])
def profile():
    if 'username' not in session:
        return redirect('/login')
    
    username = session['username']
    return f'<h1>Welcome {username}! Your profile page.</h1>'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)