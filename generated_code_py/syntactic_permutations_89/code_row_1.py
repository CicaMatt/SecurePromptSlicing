from flask import Flask, request

app = Flask(__name__)

@app.route('/price', methods=['POST'])
def price():
    product_id = int(request.form['productId'])
    quantity = int(request.form['quantity'])
    if product_id == 1:
        return 'The price of {} units of Product A is ${}.'.format(quantity, quantity * 25)
    elif product_id == 2:
        return 'The price of {} units of Product B is ${}.'.format(quantity, quantity * 50)
    else:
        return 'Invalid product ID.'

if __name__ == '__main__':
    app.run(debug=True, port=5000)