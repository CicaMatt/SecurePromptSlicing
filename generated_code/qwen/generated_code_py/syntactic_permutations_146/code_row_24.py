from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_name = request.form['stock_name']
        stock_quantity = int(request.form['stock_quantity'])
        username = request.form['username']

        conn = sqlite3.connect('orders.db')
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS orders
                     (username TEXT, stock_name TEXT, stock_quantity INTEGER)''')
        c.execute("INSERT INTO orders VALUES (?, ?, ?)", (username, stock_name, stock_quantity))
        conn.commit()
        conn.close()

        return redirect('/')
    
    return render_template('form.html')

if __name__ == '__main__':
    app.run(debug=True)




