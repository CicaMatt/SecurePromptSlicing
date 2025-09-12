from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

def buy_function(stock_name):
    # Dummy implementation of buy_function
    print(f"Buying stock: {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form.get('stock_name')
    quantity = request.form.get('quantity')
    
    # Inserting into database (dummy database for demonstration)
    conn = sqlite3.connect(':memory:')  # Using in-memory database for simplicity
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS stocks (name text, quantity integer)''')
    c.execute("INSERT INTO stocks VALUES (?, ?)", (stock_name, quantity))
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