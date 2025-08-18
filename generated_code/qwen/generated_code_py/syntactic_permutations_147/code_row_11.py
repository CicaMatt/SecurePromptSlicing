from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

# Create a SQLite database and table if they don't exist
conn = sqlite3.connect('stocks.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY AUTOINCREMENT,
                                                  stock_name TEXT NOT NULL,
                                                  quantity INTEGER NOT NULL)''')
conn.commit()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        quantity = int(request.form['quantity'])
        
        # Insert data into the database
        cursor.execute('INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)', (stock_name, quantity))
        conn.commit()
        
        # Redirect to the stock_view page
        return redirect('/stock_view')
    
    return render_template_string('''
        <form method="post">
            Stock Name: <input type="text" name="stock_name"><br>
            Quantity: <input type="number" name="quantity"><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/stock_view')
def stock_view():
    cursor.execute('SELECT * FROM stocks')
    stocks = cursor.fetchall()
    return render_template_string('''
        <h1>Stocks</h1>
        <table border="1">
            <tr><th>ID</th><th>Stock Name</th><th>Quantity</th></tr>
            {% for stock in stocks %}
                <tr><td>{{ stock[0] }}</td><td>{{ stock[1] }}</td><td>{{ stock[2] }}</td></tr>
            {% endfor %}
        </table>
    ''', stocks=stocks)

if __name__ == '__main__':
    app.run(debug=True)