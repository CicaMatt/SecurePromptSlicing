from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

# Initialize the SQLite database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders
             (id INTEGER PRIMARY KEY AUTOINCREMENT,
              stock_name TEXT NOT NULL,
              quantity INTEGER NOT NULL)''')
conn.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
        conn.commit()
        return redirect('/stock_view')
    return render_template('index.html')

@app.route('/stock_view')
def stock_view():
    cursor.execute('SELECT * FROM orders')
    orders = cursor.fetchall()
    return render_template('stock_view.html', orders=orders)

if __name__ == '__main__':
    app.run(debug=True)








