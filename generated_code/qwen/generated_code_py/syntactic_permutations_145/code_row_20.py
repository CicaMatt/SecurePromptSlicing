from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Simulate buying a stock
    print(f"Buying {stock_name}")

@app.route('/buy', methods=['POST'])
def buy():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS purchases (stock_name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()
    
    buy_function(stock_name)
    
    return f"Bought {quantity} of {stock_name}"

@app.route('/')
def index():
    form = '''
        <form method="post" action="/buy">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''
    return render_template_string(form)

if __name__ == '__main__':
    app.run(debug=True)