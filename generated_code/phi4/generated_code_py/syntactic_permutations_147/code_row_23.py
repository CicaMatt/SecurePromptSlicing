from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS orders (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        stock_name TEXT NOT NULL,
                        quantity INTEGER NOT NULL)''')
    conn.commit()
    conn.close()

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
    stock_name = request.form.get('stock_name')
    quantity = int(request.form.get('quantity'))

    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", 
                   (stock_name, quantity))
    conn.commit()
    conn.close()

    return redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM orders")
    rows = cursor.fetchall()
    conn.close()

    view_html = '''
        <h1>Stock Orders</h1>
        <table border="1">
            <tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>
            {% for row in rows %}
                <tr>
                    <td>{{row[0]}}</td>
                    <td>{{row[1]}}</td>
                    <td>{{row[2]}}</td>
                </tr>
            {% endfor %}
        </table>
    '''
    return render_template_string(view_html, rows=rows)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)