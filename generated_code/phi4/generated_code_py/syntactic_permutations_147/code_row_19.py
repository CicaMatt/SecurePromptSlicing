from flask import Flask, request, render_template_string
import sqlite3

app = Flask(__name__)

# Create or connect to a SQLite database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
c = conn.cursor()

# Create table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS orders (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    stock_name TEXT NOT NULL,
    quantity INTEGER NOT NULL
)''')
conn.commit()

@app.route('/')
def index():
    return render_template_string('''
        <form action="/buy_order" method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    
    with sqlite3.connect('stocks.db') as conn:
        c = conn.cursor()
        c.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", 
                  (stock_name, quantity))
        conn.commit()

    return f"Order for {stock_name} of quantity {quantity} has been placed."

if __name__ == '__main__':
    app.run(debug=True)