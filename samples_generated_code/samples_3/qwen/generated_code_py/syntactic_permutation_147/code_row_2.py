from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite Database
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS orders (id INTEGER PRIMARY KEY AUTOINCREMENT, stock_name TEXT, quantity INTEGER)''')
conn.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        
        # Insert data into the database
        cursor.execute("INSERT INTO orders (stock_name, quantity) VALUES (?, ?)", (stock_name, quantity))
        conn.commit()
        
        return redirect('/success')
    return '''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit Order">
        </form>
    '''

@app.route('/success')
def success():
    return 'Order placed successfully!'

if __name__ == '__main__':
    app.run(debug=True)