from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    if stock_name and quantity:
        conn = sqlite3.connect('stocks.db')
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS stocks
                     (id INTEGER PRIMARY KEY, stock_name TEXT, quantity INTEGER)''')
        c.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()
        conn.close()
        
        buy_function(stock_name)
    
    return "Stock bought successfully!"

@app.route('/')
def index():
    form_html = '''
    <form action="/buy" method="post">
        Stock Name: <input type="text" name="stock_name"><br>
        Quantity: <input type="number" name="quantity"><br>
        <input type="submit" value="Buy">
    </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)