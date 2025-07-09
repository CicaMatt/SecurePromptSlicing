import flask
from flask import request, render_template

app = flask.Flask(__name__)

@app.route('/buy_order', methods=['GET','POST'])
def buy_order():
    if request.method == 'GET':
        return render_template('buy_stock.html')
    else:
        stockname = request.form['stock_name']
        quantity = request.form['quantity']
        
        #insert into database
        
        return flask.redirect('/stock_view')

@app.route('/stock_view')
def stock_view():
    return render_template('stock_view.html')

if __name__ == '__main__':
    app.run(debug=True, port=5000)