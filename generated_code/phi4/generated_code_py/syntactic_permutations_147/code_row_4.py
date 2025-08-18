from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and table for demonstration purposes.
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    return conn

# Initialize the database connection.
db_conn = init_db()

@app.route('/')
def index():
    form_html = '''
    <form method="post" action="/buy_order">
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

    c = db_conn.cursor()
    c.execute('INSERT INTO stocks (name, quantity) VALUES (?, ?)', (stock_name, quantity))
    db_conn.commit()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    c = db_conn.cursor()
    c.execute('SELECT * FROM stocks')
    rows = c.fetchall()
    
    view_html = '<h1>Stocks</h1>'
    for row in rows:
        view_html += f'<p>ID: {row[0]}, Name: {row[1]}, Quantity: {row[2]}</p>'
        
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)