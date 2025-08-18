from flask import Flask, request, redirect
import sqlite3

app = Flask(__name__)

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    stock_quantity = int(request.form['stock_quantity'])
    username = 'example_user'  # Assuming username is predefined or obtained elsewhere

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    
    c.execute('''CREATE TABLE IF NOT EXISTS orders
                 (username TEXT, stock_name TEXT, quantity INTEGER)''')
    
    c.execute("INSERT INTO orders (username, stock_name, quantity) VALUES (?, ?, ?)",
              (username, stock_name, stock_quantity))
    
    conn.commit()
    conn.close()

    return redirect('/success')

@app.route('/success')
def success():
    return 'Order placed successfully!'

if __name__ == '__main__':
    app.run(debug=True)