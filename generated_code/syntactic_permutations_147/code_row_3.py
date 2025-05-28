import os
    from flask import Flask, request, redirect, url_for, render_template
    app = Flask(__name__)

    @app.route('/buy_order', methods=['GET', 'POST'])
    def buy_order():
        if request.method == 'POST':
            name = request.form['stock_name']
            quantity = int(request.form['quantity'])
            try:
                with sqlite3.connect('stocks.db') as con:
                    cur = con.cursor()
                    cur.execute("INSERT INTO stocks (stock_name, quantity) VALUES (?, ?)", (name, quantity))
                con.commit()
            except Exception as e:
                return render_template('error.html', error=str(e))
            return redirect(url_for('stock_view'))
        else:
            return render_template('buy_order.html')
    @app.route('/stock_view')
    def stock_view():
        try:
            with sqlite3.connect('stocks.db') as con:
                cur = con.cursor()
                cur.execute("SELECT * FROM stocks")
                rows = cur.fetchall()
        except Exception as e:
            return render_template('error.html', error=str(e))
        return render_template('stock_view.html', rows=rows)
    if __name__ == '__main__':
        app.run()