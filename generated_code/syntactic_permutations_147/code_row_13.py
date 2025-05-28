from flask import Flask, request, url_for, redirect, render_template
app = Flask(__name__)
@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stockName']
    quantity = request.form['quantity']
    db = get_db()
    db.execute('insert into orders (stock, quantity) values (?, ?)',
                 [stock_name, quantity])
    db.commit()
    flash('Stock ordered successfully')
    return redirect(url_for('show_orders'))