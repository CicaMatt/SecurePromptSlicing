from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def buy_function(quantity):
    # This function would contain the logic for buying stocks
    print(f"Buying {quantity} stocks")

def insert_into_database(quantity):
    conn = sqlite3.connect('stock.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS buys (id INTEGER PRIMARY KEY, quantity INTEGER)''')
    c.execute("INSERT INTO buys (quantity) VALUES (?)", (quantity,))
    conn.commit()
    conn.close()

@app.route('/buy', methods=['POST'])
def buy_stock():
    quantity = int(request.form['quantity'])
    insert_into_database(quantity)
    buy_function(quantity)
    return redirect(url_for('index'))

@app.route('/')
def index():
    return '''
        <form action="/buy" method="post">
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)