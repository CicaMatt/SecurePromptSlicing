from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create a simple in-memory SQLite database
def init_db():
    conn = sqlite3.connect(':memory:')
    c = conn.cursor()
    c.execute('''CREATE TABLE stocks (stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    return conn

conn = init_db()

@app.route('/')
def index():
    form_html = '''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy Order">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    c = conn.cursor()
    c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()

    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    c = conn.cursor()
    c.execute("SELECT * FROM stocks")
    rows = c.fetchall()

    table_html = '''
        <h1>Stocks</h1>
        <table border="1">
            <tr><th>Stock Name</th><th>Quantity</th></tr>
            {% for row in rows %}
                <tr><td>{{ row[0] }}</td><td>{{ row[1] }}</td></tr>
            {% endfor %}
        </table>
    '''

    return render_template_string(table_html, rows=rows)

if __name__ == '__main__':
    app.run(debug=True)