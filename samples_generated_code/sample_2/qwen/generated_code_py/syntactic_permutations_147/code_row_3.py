from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database and table for demonstration purposes
conn = sqlite3.connect('example.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
conn.commit()

@app.route('/', methods=['GET'])
def index():
    form_html = '''
    <form action="/buy_order" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Submit Order">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    
    return redirect('/stock_view')

@app.route('/stock_view', methods=['GET'])
def stock_view():
    cursor.execute("SELECT * FROM orders")
    orders = cursor.fetchall()
    
    table_html = '<h2>Stock Orders</h2><table border="1"><tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>'
    for order in orders:
        table_html += f'<tr><td>{order[0]}</td><td>{order[1]}</td><td>{order[2]}</td></tr>'
    table_html += '</table>'
    
    return render_template_string(table_html)

if __name__ == '__main__':
    app.run(debug=True)