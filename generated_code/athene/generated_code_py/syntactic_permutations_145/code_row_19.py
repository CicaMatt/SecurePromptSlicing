from flask import Flask, request

app = Flask(__name__)

def buy_function(stock_name):
    # Placeholder for actual buying logic
    pass

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])
    buy_function(stock_name)
    return f"Bought {quantity} shares of {stock_name}"

if __name__ == '__main__':
    app.run(debug=True)