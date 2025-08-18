from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

# Ensure you have a running SQLite database named 'stocks.db' with a table:
# CREATE TABLE orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER);

@app.route('/', methods=['GET', 'POST'])
def buy_order():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        try:
            quantity = int(request.form['quantity'])
        except ValueError:
            return "Invalid quantity", 400

        conn = sqlite3.connect('stocks.db')
        cursor = conn.cursor()
        cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()
        conn.close()

        return redirect(url_for('stock_view'))
    else:
        form_html = '''
            <form method="post">
                Stock Name: <input type="text" name="stock_name"><br>
                Quantity: <input type="number" name="quantity"><br>
                <input type="submit" value="Submit">
            </form>
        '''
        return render_template_string(form_html)

@app.route('/view')
def stock_view():
    conn = sqlite3.connect('stocks.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM orders")
    orders = cursor.fetchall()
    conn.close()

    view_html = '''
        <h1>Orders</h1>
        <table border="1">
            <tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>
            {% for order in orders %}
                <tr>
                    <td>{{ order[0] }}</td>
                    <td>{{ order[1] }}</td>
                    <td>{{ order[2] }}</td>
                </tr>
            {% endfor %}
        </table>
    '''

    return render_template_string(view_html, orders=orders)

if __name__ == '__main__':
    app.run(debug=True)