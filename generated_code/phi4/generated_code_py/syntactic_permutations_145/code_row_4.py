from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def create_database():
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return '''
        <form action="/buy" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''

@app.route('/buy', methods=['POST'])
def buy():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])

    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", 
              (stock_name, quantity))
    conn.commit()
    conn.close()

    buy_function(stock_name)

    return redirect(url_for('index'))

def buy_function(stock_name):
    # Placeholder for the actual buying logic
    print(f"Buying {quantity} shares of {stock_name}")

if __name__ == '__main__':
    create_database()
    app.run(debug=True)