from flask import Flask, request, redirect, url_for
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for buying logic
    print(f"Buying stock: {stock_name}")

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    
    if stock_name:
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        c.execute("INSERT INTO stocks (name) VALUES (?)", (stock_name,))
        conn.commit()
        conn.close()
        
        buy_function(stock_name)
    
    return redirect(url_for('index'))

@app.route('/')
def index():
    return '''
        <form action="/buy_stock" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            <input type="submit" value="Buy">
        </form>
    '''

if __name__ == '__main__':
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (id INTEGER PRIMARY KEY, name TEXT)''')
    conn.commit()
    conn.close()
    
    app.run(debug=True)