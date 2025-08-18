from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database
def init_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Initialize the database
db_conn = init_db()

@app.route('/')
def index():
    form_html = '''
    <form action="/buy_order" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    cursor = db_conn.cursor()
    cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', 
                   (stock_name, quantity))
    db_conn.commit()

    return redirect(url_for('stock_view', stock_id=cursor.lastrowid))

@app.route('/stock_view/<int:stock_id>')
def stock_view(stock_id):
    cursor = db_conn.cursor()
    cursor.execute('SELECT stock_name, quantity FROM stocks WHERE id=?', (stock_id,))
    row = cursor.fetchone()

    view_html = f'''
    <h1>Stock Details</h1>
    <p>Stock Name: {row[0]}</p>
    <p>Quantity: {row[1]}</p>
    '''
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)