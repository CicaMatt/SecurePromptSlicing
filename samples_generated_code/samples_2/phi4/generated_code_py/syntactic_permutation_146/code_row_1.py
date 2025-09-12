from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buy_orders (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    stock_name TEXT NOT NULL,
                    quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/buy', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])

        # Insert into database
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        c.execute('INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)', 
                  (stock_name, quantity))
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

@app.route('/profile')
def profile():
    return "Welcome to your profile!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)