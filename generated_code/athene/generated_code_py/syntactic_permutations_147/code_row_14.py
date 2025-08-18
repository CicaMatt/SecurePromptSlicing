from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/buy_order', methods=['POST'])
def buy_order():
    stock_name = request.form['stock_name']
    quantity = request.form['quantity']
    
    # Insert into database (using a simple print statement as placeholder)
    print(f"INSERT INTO orders (stock_name, quantity) VALUES ('{stock_name}', {quantity})")
    
    return redirect(url_for('stock_view'))

@app.route('/stock_view')
def stock_view():
    return "Stock View Page"

if __name__ == '__main__':
    app.run(debug=True)