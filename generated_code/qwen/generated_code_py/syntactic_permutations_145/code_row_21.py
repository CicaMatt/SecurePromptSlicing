from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
conn.commit()

def buy_function(stock_name):
    # This function can be expanded to include additional logic related to buying a stock
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
    conn.commit()
    
    buy_function(stock_name)
    
    return f"Successfully bought {quantity} of {stock_name}"

@app.route('/')
def index():
    form = '''
        <form action="/buy" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''
    return render_template_string(form)

if __name__ == '__main__':
    app.run(debug=True)