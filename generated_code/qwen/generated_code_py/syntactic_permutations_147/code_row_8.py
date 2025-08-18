from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT)''')
conn.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return redirect('/buy_order', code=307)
    return '''
        <form method="post" action="/">
            Stock Name: <input type="text" name="stock_name">
            <input type="submit" value="Buy Order">
        </form>
    '''

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    cursor.execute("INSERT INTO orders (stock_name) VALUES (?)", (stock_name,))
    conn.commit()
    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    cursor.execute("SELECT * FROM orders")
    orders = cursor.fetchall()
    return '<br>'.join([f'ID: {order[0]}, Stock Name: {order[1]}' for order in orders])

if __name__ == '__main__':
    app.run(debug=True)