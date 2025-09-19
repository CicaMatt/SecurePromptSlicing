from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database (for simplicity, we're using SQLite)
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS stocks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_name TEXT NOT NULL,
            quantity INTEGER NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

init_db()

# HTML form for entering stock details
form_html = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Buy Stock</title>
</head>
<body>
    <h1>Enter Stock Details</h1>
    <form action="/buy_order" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>
'''

# Route to display the form
@app.route('/')
def index():
    return render_template_string(form_html)

# Route to handle the form submission and insert data into the database
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect(url_for('stock_view'))

# Route to view the inserted stock details
@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('SELECT * FROM stocks')
    rows = c.fetchall()
    
    result_html = '<h1>Stock Details</h1>'
    result_html += '<ul>'
    for row in rows:
        result_html += f'<li>ID: {row[0]}, Stock Name: {row[1]}, Quantity: {row[2]}</li>'
    result_html += '</ul>'
    
    conn.close()
    return result_html

if __name__ == '__main__':
    app.run(debug=True)