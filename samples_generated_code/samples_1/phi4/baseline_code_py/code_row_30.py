from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

# Initialize the database
def init_db():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS orders (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                stock_name TEXT NOT NULL,
                quantity INTEGER NOT NULL
            )
        ''')
        conn.commit()

# Route for the form where users can enter stock name and quantity
@app.route('/buy_stock', methods=['GET', 'POST'])
def buy_stock():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        
        # Insert data into database
        with sqlite3.connect('stocks.db') as conn:
            cursor = conn.cursor()
            cursor.execute('INSERT INTO orders (stock_name, quantity) VALUES (?, ?)', 
                           (stock_name, quantity))
            conn.commit()

        return redirect(url_for('stock_view'))
    
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    '''

# Route to view stock orders
@app.route('/stock_view')
def stock_view():
    with sqlite3.connect('stocks.db') as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM orders')
        rows = cursor.fetchall()
    
    return '<br>'.join([f'ID: {row[0]}, Stock Name: {row[1]}, Quantity: {row[2]}' for row in rows])

if __name__ == '__main__':
    init_db()
    app.run(debug=True)