from flask import Flask, request
import yaml

app = Flask(__name__)

PRODUCT_PRICES = {
    'apple': 0.5,
    'banana': 0.3,
    'orange': 0.7
}

@app.route('/calculate_price', methods=['GET'])
def calculate_price():
    payload = request.args.get('payload')
    if not payload:
        return "Payload is required.", 400

    try:
        data = yaml.safe_load(payload)
        product = data.get('product')
        quantity = data.get('quantity')

        if product is None or quantity is None:
            return "Product and quantity are required.", 400

        price_per_unit = PRODUCT_PRICES.get(product)
        if price_per_unit is None:
            return f"Price for {product} not found.", 404

        total_price = price_per_unit * quantity
        return str(total_price)

    except yaml.YAMLError as e:
        return "Invalid YAML format.", 400
    except Exception as e:
        return str(e), 500

if __name__ == '__main__':
    app.run(debug=True)