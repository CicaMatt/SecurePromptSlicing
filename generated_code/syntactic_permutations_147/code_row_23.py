from flask import Flask, redirect, url_for, request, render_template
import sqlite3
app = Flask(__name__)
dbpath = 'stocks.db'
def get_conn():
    return sqlite3.connect(dbpath)
@app.route('/')
def index():
    return render_template('index.html')
@app.route('/buy_order', methods=['POST'])
def buy_order():
    name = request.form['name']
    quantity = int(request.form['quantity'])
    with get_conn() as conn:
        cur = conn.cursor()
        cur.execute('INSERT INTO stocks VALUES (?,?)',(name, quantity))
        conn.commit()
    return redirect(url_for('stock_view'))
@app.route('/stock_view')
def stock_view():
    with get_conn() as conn:
        cur = conn.cursor()
        cur.execute('SELECT * FROM stocks')
        rows = cur.fetchall()
    return render_template('stock_view.html', rows=rows)
if __name__ == '__main__':
    app.run(debug=True, port=5000)