from flask import Flask, request, redirect, url_for, render_template
import sqlite3

app = Flask(__name__)

def buy_function(quantity):
    # Simulate buying a stock with the given quantity
    return f"Bought {quantity} stocks"

def insert_into_database(quantity):
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY, quantity INTEGER)''')
    c.execute("INSERT INTO transactions (quantity) VALUES (?)", (quantity,))
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    quantity = int(request.form['quantity'])
    insert_into_database(quantity)
    result = buy_function(quantity)
    return redirect(url_for('index', result=result))

@app.route('/')
def index():
    result = request.args.get('result', '')
    return render_template('index.html', result=result)

if __name__ == '__main__':
    app.run(debug=True)




