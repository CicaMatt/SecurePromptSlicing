from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# HTML form for user input
form_html = '''
<form method="post" action="{{ url_for('buy_order') }}">
    Stock Name: <input type="text" name="stock_name"><br>
    Quantity: <input type="number" name="quantity"><br>
    <input type="submit" value="Submit">
</form>
'''

# Route to display the form
@app.route('/')
def index():
    return render_template_string(form_html)

# Route to handle form submission and insert data into database
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    
    # Create table if it does not exist
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
    
    # Insert data into table
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    # Redirect to the stock_view page
    return redirect(url_for('stock_view'))

# Route to display the contents of the database
@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    # Simple HTML table to display orders
    view_html = '<table border="1"><tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>'
    for order in orders:
        view_html += f'<tr><td>{order[0]}</td><td>{order[1]}</td><td>{order[2]}</td></tr>'
    view_html += '</table>'
    
    return render_template_string(view_html)

if __name__ == '__main__':
    app.run(debug=True)