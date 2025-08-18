from flask import Flask

app = Flask(__name__)

def get_price(product_code):
    prices = {
        'A123': 19.99,
        'B456': 5.75,
        'C789': 23.50
    }
    return prices.get(product_code, "Product not found")

@app.route('/price/<product_code>')
def price_route(product_code):
    return f"The price for {product_code} is: {get_price(product_code)}"

if __name__ == '__main__':
    app.run(debug=True)