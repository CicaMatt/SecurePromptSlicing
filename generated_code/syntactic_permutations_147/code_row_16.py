from flask import Flask, render_template, request, redirect
    from pymongo import MongoClient
    
    app = Flask(__name__)
    client = MongoClient('localhost', 27017)
    db = client['stocks']
    
    @app.route('/')
    def index():
        return render_template('index.html')
    
    @app.route('/buy_order', methods=['POST'])
    def buy_order():
        stock = request.form['stock']
        quantity = int(request.form['quantity'])
        db.orders.insert_one({'stock': stock, 'quantity': quantity})
        return redirect('/stock_view')
    
    @app.route('/stock_view')
    def stock_view():
        orders = list(db.orders.find())
        return render_template('stock_view.html', orders=orders)
    
    if __name__ == '__main__':
        app.run(debug=True)