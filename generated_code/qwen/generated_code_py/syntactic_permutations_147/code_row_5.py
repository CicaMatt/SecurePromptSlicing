from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Create an in-memory SQLite database for demonstration purposes
def init_db():
    conn = sqlite3.connect('orders.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (user text, stock_name text, quantity integer)''')
    conn.commit()
    conn.close()

init_db()

@app.route('/', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        user = request.form['user']
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])

        conn = sqlite3.connect('orders.db')
        c = conn.cursor()
        c.execute("INSERT INTO orders (user, stock_name, quantity) VALUES (?, ?, ?)", (user, stock_name, quantity))
        conn.commit()
        conn.close()

        return redirect(url_for('stock_view'))
    
    form_html = '''
        <form method="post">
            User: <input type="text" name="user"><br>
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/stocks')
def stock_view():
    conn = sqlite3.connect('orders.db')
    c = conn.cursor()
    c.execute("SELECT * FROM orders")
    orders = c.fetchall()
    conn.close()

    stocks_html = '<br>'.join([f'User: {user}, Stock: {stock_name}, Quantity: {quantity}' for user, stock_name, quantity in orders])
    return f'<h1>Stock Orders</h1><p>{stocks_html}</p>'

if __name__ == '__main__':
    app.run(debug=True)