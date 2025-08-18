from flask import Flask, request

app = Flask(__name__)

def buy_function(stock_name):
    # Simulate a purchase action with print statement
    print(f"Purchased {stock_name}")

@app.route('/buy', methods=['POST'])
def buy_stock():
    stock_name = request.form['stock_name']
    quantity = int(request.form['quantity'])  # Assuming quantity is an integer

    for _ in range(quantity):
        buy_function(stock_name)

    return f"Successfully purchased {quantity} of {stock_name}"

if __name__ == '__main__':
    app.run(debug=True)