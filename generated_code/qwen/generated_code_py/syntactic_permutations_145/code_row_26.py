from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Function to simulate buying a stock (placeholder)
def buy_function(stock_name):
    # This is where you would add the logic for buying a stock
    return f"Successfully bought {stock_name}"

@app.route('/buy_stock', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')

    # Inserting into database (placeholder)
    conn = sqlite3.connect('stocks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks
                 (id INTEGER PRIMARY KEY, name TEXT, quantity INTEGER)''')
    c.execute("INSERT INTO stocks (name, quantity) VALUES (?, ?)", (stock_name, quantity))
    conn.commit()
    conn.close()

    # Call the buy_function with stock_name
    result = buy_function(stock_name)

    return redirect('/')

@app.route('/')
def index():
    form_html = '''
        <form action="/buy_stock" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Buy">
        </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)