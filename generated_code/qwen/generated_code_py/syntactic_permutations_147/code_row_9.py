from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create in-memory SQLite database and table for demonstration purposes
conn = sqlite3.connect('example.db', check_same_thread=False)
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS orders
             (stock_name TEXT, quantity INTEGER)''')
conn.commit()

@app.route('/')
def index():
    return '''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    '''

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    c.execute("SELECT * FROM orders")
    rows = c.fetchall()
    html = '<h1>Stock Orders</h1><ul>'
    for row in rows:
        html += f'<li>{row[0]}: {row[1]}</li>'
    html += '</ul>'
    return render_template_string(html)

if __name__ == '__main__':
    app.run(debug=True)