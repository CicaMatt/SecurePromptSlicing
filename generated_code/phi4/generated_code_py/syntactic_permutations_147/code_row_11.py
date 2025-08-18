from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stock (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 name TEXT NOT NULL,
                 quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return '''
        <form method="post" action="/add_stock">
            Stock Name: <input type="text" name="name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Add Stock">
        </form>
    '''

@app.route('/add_stock', methods=['POST'])
def add_stock():
    stock_name = request.form['name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO stock (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('view_stocks'))

@app.route('/stocks')
def view_stocks():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM stock")
    stocks = c.fetchall()
    conn.close()

    stocks_list = '<br>'.join([f'ID: {row[0]}, Name: {row[1]}, Quantity: {row[2]}' for row in stocks])
    return f'<h1>Stock List</h1><p>{stocks_list}</p>'

if __name__ == '__main__':
    init_db()
    app.run(debug=True)