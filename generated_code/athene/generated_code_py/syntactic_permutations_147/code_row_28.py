from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    
    # Simple in-memory "database" for demonstration
    database = []
    database.append({'stock_name': stock_name, 'quantity': int(quantity)})
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    # For demonstration, we're just returning a simple string
    return "Order placed successfully. Redirected to stock view."

if __name__ == '__main__':
    app.run(debug=True)