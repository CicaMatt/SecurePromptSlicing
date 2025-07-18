import sqlite3
from flask import Flask,redirect, url_for, render_template, request
app = Flask(__name__)
@app.route("/buy_order", methods=['POST'])
def buy_order():
    try:
        stock_name = request.form["stockName"]
        quantity = int(request.form["quantity"])
        with sqlite3.connect("database.db") as con:
            cur = con.cursor()
            cur.execute("INSERT INTO stocks (StockName, Quantity) VALUES(?, ?)", (stock_name, quantity))
            con.commit()
    except:
        return "There was an error"
    finally:
        return redirect(url_for('stock_view'))
@app.route("/")
def stock_view():
    try:
        with sqlite3.connect("database.db") as con:
            cur = con.cursor()
            cur.execute("SELECT * FROM stocks")
            rows = cur.fetchall()
            return render_template('stock_listing.html', rows=rows)
    except:
        return "There was an error"
if __name__ == '__main__':
   app.run(debug=True)