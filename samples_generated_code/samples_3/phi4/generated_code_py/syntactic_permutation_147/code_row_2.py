from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Initialize Database (Run once)
def init_db():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS orders 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        return redirect(url_for('buy_order', stock_name=stock_name, quantity=quantity))
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''

@app.route('/buy_order')
def buy_order():
    stock_name = request.args.get('stock_name')
    quantity = int(request.args.get('quantity'))
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    return f'Order placed for {quantity} of stock {stock_name}. Redirecting...<br><a href="/">Go Back</a>'

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)